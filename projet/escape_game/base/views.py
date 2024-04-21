from django.shortcuts import render, redirect
from django.contrib.auth.forms import UserCreationForm
from django.contrib.auth.decorators import login_required
import requests

def action_led(request, etat):
    ESP32_IP = '192.168.1.195'
    if etat == 'on':
        requests.get(f'http://{ESP32_IP}/ledon')
        request.session['led_state'] = 'allumée'  # Stocker l'état dans la session
    elif etat == 'off':
        requests.get(f'http://{ESP32_IP}/ledoff')
        request.session['led_state'] = 'éteinte'  # Stocker l'état dans la session
    return redirect('base:home')

@login_required
def home(request):
 led_state = request.session.get('led_state', 'inconnu')
 return render(request, "home.html", {'led_state': led_state})


def authView(request):
 if request.method == "POST":
  form = UserCreationForm(request.POST or None)
  if form.is_valid():
   form.save()
   return redirect("base:login")
 else:
  form = UserCreationForm()
 return render(request, "registration/signup.html", {"form": form})
