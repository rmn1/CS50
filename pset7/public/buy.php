<?php

    require("../includes/config.php"); 
    $id = $_SESSION["id"];

    if ($_SERVER["REQUEST_METHOD"] == "GET")
    {
        render("buy_form.php", ["title" => "Sell"]);
    }
    else
    {
        $symbol = strtoupper($_POST["symbol"]);
        $share_amt = $_POST["share_amt"];
        
        // error if no symbol or number of shares to buy entered
        if ((empty($symbol)) || empty($share_amt))
        {
            apologize("Please specify stock and number of shares to buy.");
        }
        
        // validate only whole shares are submitted
        if (preg_match("/^\d+$/", $share_amt) == false)
        {
            apologize("Only whole shares can be purchased.");
        }
        
        // validate is numeric amount
        if (!is_numeric($share_amt))
        {
            apologize("Please enter a valid amount.");
        }
        
        $stock = lookup($symbol);
        // validate stock symbol
        if ($stock === false)
        {
            apologize("Please enter a valid stock symbol.");
        }
        
        // confirm sufficient cash is available
        $cost = $stock["price"] * $share_amt;
        $available_cash = CS50::query("SELECT cash FROM users WHERE id = ?", $id);
        if ($cost > $available_cash[0]["cash"])
        {
            apologize("You do not have sufficient cash to make this purchase.");
        }
        
        // execute transaction - increase stockholdings, decrease cash and record transaction in history table
        CS50::query("INSERT INTO portfolios (user_id, symbol, shares) VALUES (?, ?, ?) ON DUPLICATE KEY UPDATE shares = shares + VALUES(shares)", $id, $symbol, $share_amt);
        CS50::query("UPDATE users SET cash = cash - ? WHERE id = ?", $cost, $id);
        
        CS50::query("INSERT INTO history (user_id, transaction, symbol, shares, time, price) VALUES (?, 'BUY', ?, ?, CURRENT_TIMESTAMP(), ?)", $id, $symbol, $share_amt, $stock["price"]);
        

        redirect("/");
    }

?>
