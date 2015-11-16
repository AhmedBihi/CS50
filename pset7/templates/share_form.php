<table class="table table-hover">
Current funds:&nbsp;&nbsp;<b><?= "$" . number_format($_SESSION["cash"], 2) ?></b><br/>
    <thead>
        <tr>
            <th>Symbol</th>
            <th>Shares</th>
            <th>Price</th>
        </tr>
    </thead>
    <tbody>
        <?php
        foreach ($shares as $item){
            print("<tr>");
            print("<td>{$item["symbol"]}</td>");
            print("<td>{$item["shares"]}</td>");
            print("<td>{$item["price"]}</td>");
            print("</tr>");
        }
        ?>
    </tbody>
</table>
