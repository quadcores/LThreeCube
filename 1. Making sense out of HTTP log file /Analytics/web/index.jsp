<%-- 
    Document   : index
    Author     : vedangjoshi
--%>

<%@page contentType="text/html" pageEncoding="UTF-8"%>
<!DOCTYPE html>
<html>
    <head>
        <meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
        <title>JSP Page</title>
        <link rel="stylesheet" type="text/css" href="newcss.css">
    </head>
 
    <body bgcolor="d9edf7">
        <br>
        <br>
        <div class="division">
            <form method="GET" name="DrawCharts" action="My" >
            <table bgcolor="lightblue" width="280" height="100" class="customers">
                <tbody>
                <h1> &nbsp Http Data-Analysis </h1>
                    <tr class="alt">
                        <td>Access-method Distribution </td>
                        <td><input type="radio" name="Distributions" value="method" /></td>
                    </tr>
                    <tr class="alt1">
                        <td>Response Code</td>
                        <td><input type="radio" name="Distributions" value="response" /></td>
                    </tr>

                    <tr class="alt">
                        <td>Country-wise-requests</td>
                        <td><input type="radio" name="Distributions" value="country" /></td>
                    </tr>
                    
                    <tr class="alt1">
                        <td>View Packet Details</td>
                        <td><input type="radio" name="Distributions" value="packet" /></td>
                    </tr>
                <td colspan="2">
                    <input type="submit" value="Go!" name="get"/>
                </td>
                </tr>
                </tbody>
            </table>  
        </style>
    </head>
</html>
