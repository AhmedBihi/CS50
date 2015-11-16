<?php

    // configuration
    require("../includes/configs.php"); 
    
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
    
    // render portfolio
    render("portfolio.php", ["title" => "Portfolio", "shares" => $shares, "cash" => $_SESSION["cash"]]);

?>
