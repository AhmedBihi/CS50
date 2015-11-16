<table class="table table-hover">
    <thead>
        <tr>
            <th>Action</th>
            <th>Symbol</th>
            <th>Shares</th>
            <th>Price</th>
            <th>Date</th>
        </tr>
    </thead>
    <tbody>
        <?php
        foreach ($history as $item){
            print("<tr>");
            print("<td>{$item["action"]}</td>");
            print("<td>{$item["symbol"]}</td>");
            print("<td>{$item["shares"]}</td>");
            print("<td>{$item["price"]}</td>");
            print("<td>{$item["date"]}</td>"); 
            print("</tr>");
        }
        ?>
    </tbody>
</table>
