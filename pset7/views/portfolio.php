<div class="portfolio_table">
    <table class="table table-striped">
        <thead>
            
            <tr>
                <th>Symbol</th>
                <th>Name</th>
                <th>Shares</th>
                <th>Price</th>
                <th>TOTAL</th>
            </tr>
            
        </thead>
    
        <tbody>
           
            <?php foreach ($positions as $position): ?>
                <tr>        
                    <td><?=strtoupper($position["symbol"])?></td>
                    <td><?=$position["name"]?></td>
                    <td><?=number_format($position["shares"])?></td>
                    <td>$<?=number_format($position["price"],2)?></td>
                    <td>$<?=number_format(($position["price"] * $position["shares"]),2)?></td>
                </tr>
            <?php endforeach; ?>
            
            <tr>
                <td><strong>Total Value of Shareholdings</strong></td>
                <td>-</td><td>-</td><td>-</td>
                <td><strong>$<?=number_format($total_value,2)?></strong></td>
            </tr>
            
            <tr>
                <td><strong>Cash Balance</strong></td>
                <td>-</td><td>-</td><td>-</td>
                <td><strong>$<?=number_format($cash_balance,2)?></strong></td>
            </tr>
            
            <tr>
                <td><strong>Total Portfolio Value</strong></td>
                <td>-</td><td>-</td><td>-</td>
                <td><strong>$<?=number_format(($total_value + $cash_balance),2)?></strong></td>
            </tr>
            
        </tbody>
    </table>
</div>