#include <Arduino.h>

const char settingspage[] PROGMEM = R"=====(
  <!DOCTYPE html>
  <html>
  <head>
  <meta charset="utf-8" name="viewport" content="width=device-width initial-scale=1">
  <title>Settings</title>
  <style type="text/css">

  :root {
    font-family: Helvetica;
    width: 100%;
    max-width: 100%;
    max-height: 100%;
    overflow: hidden;
  }

  .settings-link {
    position:absolute;
     left:0px;
     bottom:0px;
     height:60px;
     width:100%;
  }

  .centralblock {
        position: fixed;
        top: 50%;
        left: 50%;
        transform: translate(-50%, -50%);
      }

    .button {
        font-weight: 700;
        color: white;
        text-decoration: none;
        padding: .8em 1em calc(.8em + 3px);
        border-radius: 3px;
        background: #24744c;
        box-shadow: 0 -3px rgb(53,167,110) inset;
        transition: 0.2s;
      }
      .button:hover { background: rgb(53, 167, 110); }
      .button:active {
        background: rgb(33,147,90);
        box-shadow: 0 3px rgb(33,147,90) inset;
      }

      input[type="text"], textarea {
      background: #f9f9f9;
      border: 1px solid #ccc;
      box-shadow: inset 1px 1px 1px rgba(0,0,0,0.1);
      padding: 2px;
  }
  </style>
  </head>
  <body>
  <center>
  <div class="centralblock">
  	<div>
  		<h1><span>&#9881;</span> Settings</h1><br>
      <form name="test" method="post" action="input1.php">
   <p><b>Set temperature:</b><br>
    <input type="text">
   </p>
   <p><b>Set humidity:</b><br>
    <input type="text">
   </p>
   <p><b>Set hysteresis:</b><br>
    <input type="text">
   </p>
      <button class="button">💾 Save</button>
  	</div>
  	 <br>
  </div>
  <div class="settings-link">
  	<a class="button" href="/"> 🔙 Back</a>
  </div>
  <script>

  </script>
  </center>
  </body>
  </html>

)=====";
