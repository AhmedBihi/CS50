<?php
    // configuration
    require("../includes/config.php");
    
    $rows = query("SELECT CASE WHEN type = 1 THEN 'BUY' ELSE 'SELL' END action, symbol,
    shares, price, date FROM history WHERE user_id = ? order by date desc", $_SESSION["id"]);
    
    if(count($rows) == 0)
    {
        apologize("Your history is empty ;)");
    }
    
    render("history_page.php", ["title" => "History", "history" => $rows]);
?>
