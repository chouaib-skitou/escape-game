from django.shortcuts import redirect, render
import requests

def index(request):
    # Récupérer l'état de la LED de la session, ou 'inconnu' si non défini
    led_state = request.session.get('led_state', 'inconnu')
    return render(request, 'controle_led/index.html', {'led_state': led_state})

def action_led(request, etat):
    ESP32_IP = '172.20.10.9'  # Utilisez l'adresse IP réelle de l'ESP32
    if etat == 'on':
        requests.get(f'http://{ESP32_IP}/ledon')
        request.session['led_state'] = 'allumée'  # Stocker l'état dans la session
    elif etat == 'off':
        requests.get(f'http://{ESP32_IP}/ledoff')
        request.session['led_state'] = 'éteinte'  # Stocker l'état dans la session
    return redirect('index')


# from django.shortcuts import redirect, render
# import serial
# import serial.tools.list_ports

# def trouver_port_esp32():
#     ports = serial.tools.list_ports.comports()
#     for port in ports:
#         print(f"Port: {port.device}, Description: {port.description}")
        
#         if "CH340" in port.description:  # Ajouté pour détecter l'ESP32 avec le convertisseur CH340
#             return port.device

#     return None  


# def index(request):
#     # Récupérer l'état de la LED de la session, ou 'inconnu' si non défini
#     led_state = request.session.get('led_state', 'inconnu')
#     return render(request, 'controle_led/index.html', {'led_state': led_state})

# def action_led(request, etat):
#     port_esp32 = trouver_port_esp32()  
#     if port_esp32:
#         try:
#             with serial.Serial(port_esp32, 115200, timeout=1) as ser:
#                 if etat == 'on':
#                     ser.write(b'LED_ON\n')
#                     request.session['led_state'] = 'allumée'
#                 elif etat == 'off':
#                     ser.write(b'LED_OFF\n')
#                     request.session['led_state'] = 'éteinte'
#         except serial.SerialException as e:
#             print(f"Erreur de connexion au port série : {e}")
#     else:
#         print("ESP32 non trouvé.")
    
#     return redirect('index')




