"""Views file for Django"""
from django.http import HttpResponse, JsonResponse
from django.shortcuts import redirect
import socket

def rev_commande(request):
    if request.method=="POST":
        plate = request.POST["plate"]
        email = request.POST["email"]
        plate_as_bytes = str.encode(plate)
        print(f"se pidio un {plate_as_bytes} para {email}")
        try:
            server_ip = "192.168.1.32"
            server_port = 333
            kitchen = socket.socket()
            print(kitchen)
            kitchen.connect((server_ip, server_port))
            kitchen.send(str.encode(plate))
            kitchen.close()
            return HttpResponse("buena crack")
        except Exception as e:
            return HttpResponse(e)
    else:
        return redirect("home")

def api1(request, commande):
    data = {"data":"buena"}
    print(commande)
    return JsonResponse(data)

def send_data(request):
    try:
        server_ip = "192.168.1.32"
        server_port = 333
        kitchen = socket.socket()
        print(kitchen)
        kitchen.connect((server_ip, server_port))
        kitchen.send(b"N:Pates bolognese")
        kitchen.send(b"O:115\n")
        kitchen.send(b"e")
        kitchen.close()
        return HttpResponse("buena crack")
    except Exception as e:
        return HttpResponse(e)

