<?php

    // configuration
    require("../includes/config.php"); 

    if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        if (empty($_POST["symbol"]))
        {
            apologize("Please provide a stock symbol.");
        }
        
        $symbol = lookup($_POST["symbol"]);
        if ($symbol === false)
        {
            apologize("Please enter a valid stock symbol.");
        }
        else
        {
            render("quote_display.php", ["title" => $symbol["name"], "symbol" => $symbol["symbol"], "price" => $symbol["price"], "name" => $symbol["name"],]);
        }
    }
    else
    {
        render("quote_form.php", ["title" => "Stock Quotes"]);
    }


?>