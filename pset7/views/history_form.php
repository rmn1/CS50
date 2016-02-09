<table class="table table-striped">

    <thead>
        <tr>
            <th>Transaction</th>
            <th>Date/Time</th>
            <th>Symbol</th>
            <th>Shares</th>
            <th>Price Per Share</th>
            <th>Transaction Value</th>
        </tr>
    </thead>

    <tbody>

        <?php foreach ($transactions as $transaction): ?>
            <tr>        
                <td><?=$transaction["transaction"]?></td>
                <td><?=date('M. j, Y, H:i', strtotime($transaction["time"]))?></td>
                <td><?=$transaction["symbol"]?></td>
                <td><?=$transaction["shares"]?></td>
                <td>$<?=number_format($transaction["price"],2)?></td>
                <td>$<?=number_format(($transaction["price"] * $transaction["shares"]),2)?></td>
            </tr>
        <?php endforeach; ?>

    </tbody>

</table>