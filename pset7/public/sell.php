<?php

    require("../includes/config.php"); 
    $id = $_SESSION["id"];

    if ($_SERVER["REQUEST_METHOD"] == "GET")
    {
        $rows = CS50::query("SELECT * FROM portfolios WHERE user_id = ?", $id);
        render("sell_form.php", ["title" => "Sell", "positions" => $rows]);
    }
    else
    {
        $symbol = $_POST["symbol"];
        $share_amt = $_POST["share_amt"];

        // error if no symbol or number of shares to buy entered
        if ((empty($symbol)) || empty($share_amt))
        {
            apologize("Please specify stock and number of shares to sell.");
        }

        // validate only whole shares are submitted
        if (preg_match("/^\d+$/", $share_amt) == false)
        {
            apologize("Only whole shares can be sold.");
        }
        
        // validate is numeric amount
        if (!is_numeric($share_amt))
        {
            apologize("Please enter a valid amount.");
        }
        
        // confirm user owns sufficient shares for the sale
        $ownership = CS50::query("SELECT * FROM portfolios WHERE user_id = ? AND symbol = ?", $id, $symbol);
        if (empty($ownership))
        {
            apologize("You do not own any {$symbol} stock.");
        }
        else
        {
            $shares = $ownership[0]["shares"];
            $quote = lookup($symbol);
            if ($share_amt > $shares)
            {
                apologize("You do not own enough shares to make this sale.");
            }
            
            // if all shares of such stock are sold, remove stock entirely
            elseif ($share_amt == $shares)
            {
                CS50::query("DELETE FROM portfolios WHERE user_id = ? and symbol = ?", $id, $symbol);
            }
            
            // if only some shares sold, update holdings accordingly
            else
            {
                CS50::query("UPDATE portfolios SET shares = ? WHERE symbol = ? and user_id = ?", ($shares - $share_amt), $symbol, $id);
            }
            
            // update user's cash to account for transaction
            $proceeds = $quote["price"] * $share_amt;
            CS50::query("UPDATE users SET cash = cash + ? WHERE id = ?", $proceeds, $id);
            
            // record transaction history
            CS50::query("INSERT INTO history (user_id, transaction, symbol, shares, time, price) VALUES (?, 'SELL', ?, ?, CURRENT_TIMESTAMP(), ?)", $id, $symbol, $share_amt, $quote["price"]);
            
            redirect("/");
        }
    }

?>
