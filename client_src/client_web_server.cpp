#include "config.h"
#include "client_web_server.h"

String logBuffer = "";

const char html_page[] PROGMEM = R"rawliteral(
<html>
  <head>
    <title>Dormcehck Client Node</title>
    <style>
      body {
        font-family: Arial, sans-serif;
        background-color: #f4f4f9;
        color: #333;
        margin: 0;
        padding: 0;
      }
      header {
        background-color: #2c3e50;
        color: #fff;
        padding: 15px 0;
        text-align: center;
      }
      header h1 {
        margin: 0;
        font-size: 2em;
      }
      nav {
        background-color: #34495e;
        overflow: hidden;
      }
      nav a {
        float: left;
        display: block;
        color: white;
        padding: 14px 20px;
        text-align: center;
        text-decoration: none;
        font-size: 1.2em;
      }
      nav a:hover {
        background-color: #1abc9c;
      }
      .content {
        margin: 20px;
      }
      .tab-content {
        display: none;
      }
      .tab-content.active {
        display: block;
      }
      .logo {
        max-width: 150px;
        margin-top: 10px;
      }
      .form-container {
        background-color: #fff;
        padding: 20px;
        border-radius: 8px;
        box-shadow: 0 4px 6px rgba(0, 0, 0, 0.1);
        margin: 20px 0;
      }
      .form-container input[type="text"],
      .form-container input[type="submit"],
      .form-container input[type="file"] {
        padding: 10px;
        font-size: 1em;
        margin: 10px 0;
        width: 100%;
        box-sizing: border-box;
        border: 1px solid #ddd;
        border-radius: 5px;
      }
      .form-container input[type="submit"] {
        background-color: #1abc9c;
        color: white;
        border: none;
        cursor: pointer;
      }
      .form-container input[type="submit"]:hover {
        background-color: #16a085;
      }
      footer {
        background-color: #2c3e50;
        color: white;
        text-align: center;
        padding: 10px;
        position: fixed;
        bottom: 0;
        width: 100%;
      }
      .login-container {
        max-width: 400px;
        margin: 50px auto;
        background-color: #fff;
        padding: 20px;
        border-radius: 8px;
        box-shadow: 0 4px 6px rgba(0, 0, 0, 0.1);
      }
      .login-container input[type="text"],
      .login-container input[type="password"] {
        width: 100%;
      }

      /* Toggle Switch Styling */
      .switch {
        position: relative;
        display: inline-block;
        width: 60px;
        height: 34px;
        vertical-align: middle;
      }

      .switch input {
        opacity: 0;
        width: 0;
        height: 0;
      }

      .slider {
        position: absolute;
        cursor: pointer;
        top: 0;
        left: 0;
        right: 0;
        bottom: 0;
        background-color: #ccc;
        transition: .4s;
        border-radius: 50px;
      }

      .slider:before {
        position: absolute;
        content: "";
        height: 26px;
        width: 26px;
        border-radius: 50px;
        left: 4px;
        bottom: 4px;
        background-color: white;
        transition: .4s;
      }

      input:checked + .slider {
        background-color: #1abc9c;
      }

      input:checked + .slider:before {
        transform: translateX(26px);
      }

      .button-container {
        display: flex;
        align-items: center;
        justify-content: space-between;
        margin-bottom: 15px;
      }

      .button-container label {
        font-size: 1.2em;
        color: #333;
      }
    </style>
  </head>
  <body>
    <!-- Authentication Page -->
    <div id="authPage" class="login-container">
      <h2>Login</h2>
      <form action="/login" method="POST">
        <label for="username">Username:</label><br>
        <input type="text" id="username" name="username" placeholder="Enter Username" required><br>
        <label for="password">Password:</label><br>
        <input type="password" id="password" name="password" placeholder="Enter Password" required><br>
        <input type="submit" value="Login">
      </form>
    </div>

    <!-- Main Content -->
    <div id="mainContent" style="display:none;">
      <header>
        <img src="logo.png" class="logo" alt="Company Logo">
        <h1>Dormcehck Client Node</h1>
      </header>

      <nav>
        <a href="#" onclick="showTab('logTab')">Cardchecks</a>
        <a href="#" onclick="showTab('settingsTab')">Settings</a>
      </nav>

      <div class="content">
        <div id="logTab" class="tab-content active">
          <h2>Cardcheck Logs</h2>
          <pre id="logContent">Loading logs...</pre>
        </div>

        <div id="settingsTab" class="tab-content">
          <h2>Settings</h2>

          <div class="form-container">
            <form action="/update" method="POST">
              <!-- Diagnostics Section -->
              <h3>Diagnostics</h3>
              <p>Uptime: 5 hours</p>
              <p>Temperature: 25 &#8451;</p>
              <p>MAC Address: 00:1A:2B:3C:4D:5E</p>
              <p>Firmware Version: 1.0.0</p>
              <p>Operation Cycles: 256</p>
            </form>
          </div>

          <!-- Wifi Form -->
          <div class="form-container">
            <form action="/update" method="POST">
              <h3>WiFi Settings</h3>
              WiFi SSID: <input type="text" name="ssid" placeholder="Enter WiFi SSID"><br>
              WiFi Password: <input type="text" name="wpassword" placeholder="Enter WiFi Password"><br>
              <input type="submit" value="Upload to device">
            </form>
          </div>
		  
		<!-- Firmware Form -->
          <div class="form-container">
			<h3>Firmware update</h3>
            <form action="/update" method="POST">
              <input type="file" name="firmware" id="firmware"><br>
              <input type="submit" value="Upload to device">
            </form>
          </div>

          <!-- Control Buttons -->
          <div class="form-container">
            <h3>Control Door, LED, and Buzzer</h3>
            <div class="button-container">
              <label for="doorToggle">Lock</label>
              <label class="switch">
                <input type="checkbox" id="doorToggle" onclick="toggleState('doorState')">
                <span class="slider"></span>
              </label>
            </div>
            <div class="button-container">
              <label for="ledToggle">LED</label>
              <label class="switch">
                <input type="checkbox" id="ledToggle" onclick="toggleState('ledState')">
                <span class="slider"></span>
              </label>
            </div>
            <div class="button-container">
              <label for="buzzerToggle">Buzzer</label>
              <label class="switch">
                <input type="checkbox" id="buzzerToggle" onclick="toggleState('buzzerState')">
                <span class="slider"></span>
              </label>
            </div>
          </div>
        </div>
      </div>

      <footer>
        <p>&copy; 2025 Freecredit Inc. All rights reserved.</p>
      </footer>
    </div>

    <script>
      function showTab(tab) {
        var tabs = document.getElementsByClassName('tab-content');
        for (var i = 0; i < tabs.length; i++) {
          tabs[i].classList.remove('active');
        }
        document.getElementById(tab).classList.add('active');
      }

      function loadLogs() {
        fetch('/logs')
          .then(response => response.text())
          .then(data => {
            document.getElementById('logContent').textContent = data;
          })
          .catch(error => {
            document.getElementById('logContent').textContent = 'Error loading logs!';
            console.error('Error fetching logs:', error);
          });
      }

      // Simulate login and show main content
      document.querySelector("form[action='/login']").onsubmit = function(e) {
        e.preventDefault();
        // Simulate successful login
        document.getElementById('authPage').style.display = 'none';
        document.getElementById('mainContent').style.display = 'block';
      };

      function toggleState(state) {
        var toggle = document.getElementById(state + "Toggle");
        // No need to update state text, sliders will indicate the state
      }
      loadLogs(); // Load logs when the page is opened
      setInterval(loadLogs, 5000); // Refresh logs every 5 second

    </script>
  </body>
</html>
)rawliteral";

// Initialize web server
void init_web_server() {
  server.on("/", HTTP_GET, handleRoot);
  server.on("/update", HTTP_POST, handleWiFiUpdate);
  server.on("/logs", HTTP_GET, handle_logs);
  server.on("/diagnostics", HTTP_GET, serveSelfDiagnostics);
  server.begin();
}

void handle_logs() {
  server.send(200, "text/plain", logBuffer);
}

void web_server_log(String message) {
  logBuffer += message + "\n";
}

void handleRoot() {
  server.send(200, "text/html", html_page);
}

void handleWiFiUpdate() {
  String ssid = server.arg("ssid");
  String password = server.arg("wpassword");
  server.send(200, "text/html", "<h1>Device Updated!</h1>");
}

void serveSelfDiagnostics() {
  String diagnostics = "Uptime: 5 hours\nTemperature: 25°C\nMAC Address: 00:1A:2B:3C:4D:5E\nFirmware Version: 1.0.0\nOperation Cycles: 256";
  server.send(200, "text/plain", diagnostics);
}
