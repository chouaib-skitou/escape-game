import requests

# Configuration
HA_URL = "http://your_home_assistant_url:8123"
ENTITY_ID = "sensor.temperature_sensor"  # Change this to your sensor's entity ID in Home Assistant
TOKEN = "YOUR_LONG_LIVED_ACCESS_TOKEN"  # Replace with the token you generated

def send_temperature(value):
    """Send temperature value to Home Assistant."""
    headers = {
        "Authorization": f"Bearer {TOKEN}",
        "content-type": "application/json",
    }
    
    data = {
        "state": str(value),
        "attributes": {
            "unit_of_measurement": "°C",
            "friendly_name": "Temperature Sensor",
        }
    }
    
    response = requests.post(f"{HA_URL}/api/states/{ENTITY_ID}", headers=headers, json=data)
    
    if response.status_code == 200:
        print("Temperature sent successfully!")
    else:
        print(f"Failed to send temperature. Status code: {response.status_code}")
        print(response.text)

if __name__ == "__main__":
    temperature_value = float(input("Enter the temperature value in °C: "))
    send_temperature(temperature_value)
