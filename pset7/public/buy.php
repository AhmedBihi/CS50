<?php

    // configuration
    require("../includes/config.php");
   
    
    if($_SERVER["REQUEST_METHOD"] == "POST")
    {
        // TODO
        if(empty($_POST["buystock"]))
        {
            apologize("Please choose a stock to buy!");
        }
        
        if(empty($_POST["shares"]) || !is_numeric($_POST["shares"]) 
                        || !preg_match("/^\d+$/", $_POST["shares"]))
        {
            apologize("Enter a legit amount of shares.");
        }
        
        $stock = lookup($_POST["buystock"]);
        
        if($stock === false)
        {
            apologize("Invalid stock symbol");
        }
        else
        {
            $value = $stock["price"] * $_POST["shares"];
            
            if($_SESSION["cash"] < $value)
            {
                apologize("You don't have enough money.");
            }
            else
            {
                $query = query("INSERT INTO portfolio(id, symbol, shares) VALUES (?, ?, ?)
                    ON DUPLICATE KEY UPDATE shares = shares + VALUES(shares)"
                    ,$_SESSION["id"], $stock["symbol"], $_POST["shares"]);
                if($query === false)
                {
                    apologize("Something went wrong while buying shares!");
                }
                
                $query = query("UPDATE users SET cash = cash - ? where id = ?", $value, $_SESSION["id"]);
                if($query === false)
                {
                    apologize("Something went wrong while updating shares!");
                }
                
                $_SESSION["cash"] -= $value;
                
                // History
                $query = query("INSERT INTO history(user_id, type, symbol, shares, price, date) VALUES (?, ?, ?, ?, ?, Now())"
                    ,$_SESSION["id"], 1, strtoupper($stock["symbol"]), $_POST["shares"], $stock["price"]);
                
                redirect("/");
            }       
        }
    }
    else
    {
        render("buy_form.php", ["title" => "Buy"]);   
    } 
  
?>
