<?php
    
    // configuration
    require("../includes/config.php");

    // if user reached page via GET (as by clicking a link or via redirect)
    if ($_SERVER["REQUEST_METHOD"] == "GET")
    {
        // else render form
        render("quote_form.php", ["title" => "Quote"]);
    }
    
    if($_SERVER["REQUEST_METHOD"] == "POST")
    {
        // TODO
        if(empty($_POST["symbol"]))
        {
            apologize("Insert a stock symbol please!");
        }
        else
        {
            if(($s = lookup($_POST["symbol"])) === false)
            {
                apologize("Not a stock!");
            }
            else
            {
                render("quote.php", [$s]);
            }    
        }    
    }
    
?>
