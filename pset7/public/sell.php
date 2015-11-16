<?php

    // configuration
    require("../includes/config.php");
    
    if($_SERVER["REQUEST_METHOD"] == "POST")
    {
        // TODO
        if(empty($_POST["sellstock"]))
        {
            apologize("Choose a stock symbol to sell please!");
        }
        
        $stock = lookup($_POST["sellstock"]);
        
        if($stock === false)
        {
            apologize("Invalid stock symbol");
        }
        else
        {
            // fetch stock prices
            $rows = query("SELECT * FROM portfolio WHERE id = ? AND symbol = ?", $_SESSION["id"], $_POST["sellstock"]);
            
            if (count($rows) == 1)
            {
                $shares = $rows[0]["shares"];
            }
            else
            {
                apologize("Shares for specified symbol not found.");
            }
            
            $value = $stock["price"] * $shares;

            $query = query("DELETE FROM portfolio WHERE id = ? AND symbol = ?", $_SESSION["id"], $_POST["sellstock"]);
            if($query === false)
            {
                apologize("Couldn't sell shares.");
            } 
        
            $query = query("UPDATE users SET cash = cash + ? WHERE id = ?", $value, $_SESSION["id"]);
            if($query === false)
            {
                apologize("Couldn't update users cash.");
            }
        
            $_SESSION["cash"] += $value;  
            
            $query = query("INSERT INTO history(user_id, type, symbol, shares, price, date) VALUES (?, ?, ?, ?, ?, Now())"
                ,$_SESSION["id"], 2, strtoupper($_POST["sellstock"]), $shares, $stock["price"]);
            
            redirect("/");
        }
    }
    else
    {
        $rows = query("SELECT symbol FROM portfolio WHERE id = ?", $_SESSION["id"]);
        render("sell_form.php", ["title" => "Buy", "stocks" => $rows]);   
    } 
  
?>
