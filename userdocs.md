<!DOCTYPE html>
<html lang="en">
    <!--Nicholas Bennington, WDD121 Basic Template-->
    <head>
        <title>Rae User Docs</title>
        <meta charset="utf-8">
        <style>
            body{
                margin-right: 50%;
                margin-left: 10%;
            }
            table{
                margin-left: 5%;
            }
            td{
                padding:5px;
                border: 1px solid black;
            }
            p{
                margin-left:5%;
            }
            h4 {
                margin-left:2.5%;
            }
        </style>
    </head>
    <header>
        <h1>Rae User Documentation</h1>
    </header>
    <body>
        <p>To Do:</p>
        <ul>
            <li>Whitespace</li>
        </ul>
        
        <h3>1-1. Types</h3>
        <p>
            Rae uses primitive types in a similar fashion to x86 assembly. 
            Types are either signed or unsigned. 
            The compiler will determine signs in numeric literal expressions. 
            It is up to the user to determine how the data is expressed and processed beyond signed/unsigned binary. 
            Type keywords consist of the following:
        </p>
        <table>
            <tr>
                <th>Type</th>
                <th>Description</th>
            </tr>
            <tr>
                <td>byte</td>
                <td>signed 8-bit</td>
            </tr>
            <tr>
                <td>ubyte</td>
                <td>unsigned 8-bit</td>
            </tr>
            <tr>
                <td>word</td>
                <td>signed 16-bit</td>
            </tr>
            <tr>
                <td>uword</td>
                <td>unsigned 16-bit</td>
            </tr>
        </table>

        <h3>1-2. Variables</h3>
        <p>
            Variable identifiers must be alphanumeric and can use underscores and hypens. 
            The first character of the identifier cannot be numerical or a hypen.
        </p>

        <h4>1-2.1. Variable Declaring, Initialization, and Assignment</h4>
        <p>
            Variable declarations must include a type keyword before the identifier separated by whitespace.
            <br><br>
            Variables can be intialized in their declaration using a single equal sign after the identifier. On the right side of the equal sign, the user can use literals, variable/preprocessor identifiers and expressions using binary operators.
            <br><br>
            All declarations, initializations, and assignments must end with a semicolon.
        </p>
    </body>
</html>
