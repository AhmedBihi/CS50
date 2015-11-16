<?php
    
    // configuration
    require("../includes/config.php"); 
    
    $rows = query("SELECT * FROM portfolio WHERE id = ?", $_SESSION["id"]);
    $cashflow = query("SELECT cash FROM users where id = ?", $_SESSION["id"]);
    $shares = [];
    
    foreach ($rows as $row)
    {
        $stock = lookup($row["symbol"]);
        if ($stock !== false)
        {
            $shares[] = [
                "name" => $stock["name"],
                "price" => $stock["price"],
                "shares" => $row["shares"],
                "symbol" => $row["symbol"]
            ];
        }
    }
    
    if(count($rows) == 0)
    {
        apologize("Buy some shares dude!");
    }
    
    render("share_form.php", ["title" => "Shares", "shares" => $shares, "cash" => $_SESSION["cash"]]);
    
?>
