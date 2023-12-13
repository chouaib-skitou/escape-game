
import requests

# Configuration de Home Assistant
HA_URL = "http://homeassistant.local:8123"
TOKEN = "eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJpc3MiOiJiN2Y2MmQ5MjVjMzM0ODAxYWVhMWI2OWYxMDdjZWRhYyIsImlhdCI6MTcwMjQ2Njg4NiwiZXhwIjoyMDE3ODI2ODg2fQ.E9OR-OPfo9gRXnp_i3GISBi6JdhLr89Z7khSKAO0_Ek"

# REST API
def make_request(ha_url, token, endpoint, method='GET', data=None):
    """
    Make a request to the Home Assistant API.

    :param ha_url: URL of the Home Assistant instance.
    :param token: Long-Lived Access Token for Home Assistant.
    :param endpoint: API endpoint to access.
    :param method: HTTP method ('GET' or 'POST').
    :param data: Data to send in case of a POST request.
    :return: Response from the API or None if the request fails.
    """
    headers = {
        "Authorization": f"Bearer {token}",
        "Content-Type": "application/json",
    }
    url = f"{ha_url}{endpoint}"

    try:
        if method == 'GET':
            response = requests.get(url, headers=headers)
        elif method == 'POST':
            response = requests.post(url, headers=headers, json=data)
        response.raise_for_status()
        return response.json()
    except requests.RequestException as e:
        print(f"Error: {e}")
        return None
    

# Get Configuration
def get_configuration():
    return make_request(HA_URL, TOKEN, "/api/config")

# Get Events
def get_events():
    return make_request(HA_URL, TOKEN, "/api/events")

# Get Services
def get_services():
    return make_request(HA_URL, TOKEN, "/api/services")

# Get States
def get_states():
    return make_request(HA_URL, TOKEN, "/api/states")


# Get History for Period
def get_history_for_period(timestamp):
    return make_request(HA_URL, TOKEN, f"/api/history/period/{timestamp}")

# Get Logbook for Timestamp
def get_logbook_for_timestamp(timestamp):
    return make_request(HA_URL, TOKEN, f"/api/logbook/{timestamp}")

# Get State by Entity ID
def get_state_by_entity_id(entity_id):
    return make_request(HA_URL, TOKEN, f"/api/states/{entity_id}")

# Get Error Log
def get_error_log():
    return make_request(HA_URL, TOKEN, "/api/error_log")

# Get Camera Proxy
def get_camera_proxy(camera_entity_id):
    return make_request(HA_URL, TOKEN, f"/api/camera_proxy/{camera_entity_id}")

# Get Calendars
def get_calendars():
    return make_request(HA_URL, TOKEN, "/api/calendars")

# Get Calendar by Entity ID
def get_calendar_by_entity_id(calendar_entity_id):
    return make_request(HA_URL, TOKEN, f"/api/calendars/{calendar_entity_id}")

# Update State
def update_state(entity_id, new_state):
    return make_request(HA_URL, TOKEN, f"/api/states/{entity_id}", method='POST', data=new_state)

# Fire Event
def fire_event(event_type, event_data=None):
    return make_request(HA_URL, TOKEN, f"/api/events/{event_type}", method='POST', data=event_data)

# Call Service
def call_service(domain, service, service_data=None):
    return make_request(HA_URL, TOKEN, f"/api/services/{domain}/{service}", method='POST', data=service_data)

# Render Template
def render_template(template_data):
    return make_request(HA_URL, TOKEN, "/api/template", method='POST', data=template_data)

# Check Configuration
def check_config():
    return make_request(HA_URL, TOKEN, "/api/config/core/check_config", method='POST')

# Handle Intent
def handle_intent(intent_data):
    return make_request(HA_URL, TOKEN, "/api/intent/handle", method='POST', data=intent_data)



states = get_states()
esphome_states = get_state_by_entity_id('update.esphome_update')


print('\n\nESPHome -------------------------------------------\n\n')
print(esphome_states)


print('\n\nAll states -------------------------------------------\n\n')
if states is not None:
    for state in states:
        print(state) 
else:
    print("Failed to retrieve states.")

