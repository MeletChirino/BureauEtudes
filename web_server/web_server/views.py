"""Views file for Django"""
#Django modules
from django.http import HttpResponse, JsonResponse
from django.shortcuts import redirect, render

#local modules
from apps.menus.models import Menu
from apps.commandes.models import Commandes
from .mails import commande_pret

#Python modules
import socket
import time

def home(request):
    menus = Menu.objects.all()
    data = {"menu": menus}
    return render(request, 'landing_page.html', context=data)

def rev_commande(request):
    if request.method=="POST":
        plate = request.POST["plate"]
        email = request.POST["email"]
        waiting_line = Commandes.objects.filter(state=2)
        plate_ = Menu.objects.get(name=plate)
        new_command = Commandes(plate=plate_, email=email)
        new_command.save()#guardar la commanda

        print(waiting_line)

        if(waiting_line):
            #if there is something in kitchen it just saves the commande
            print("Hay algo en la cocina, no se puede enviar por ahora")
            return redirect("home")
        else:
            new_command.state = 2
            new_command.save()#guardar la commanda
            print("enviando la commanda")
            comm = f"{new_command.plate};{new_command.pk}"
            plate_as_bytes = str.encode(plate)
            print(f"commande: {comm}")
            try:
                server_ip = "192.168.1.32"
                server_port = 333
                kitchen = socket.socket()
                print(kitchen)
                kitchen.connect((server_ip, server_port))
                kitchen.send(str.encode(comm))
                kitchen.close()
                return redirect("home")
            except Exception as e:
                return HttpResponse(e)
    else:
        return redirect("home")

def api1(request, commande):
    print(commande)
    if(commande == 0):
        #si es 0 revisa si hay commandes en train de faire, sino manda el waiting
        time.sleep(5)
        waiting_line = Commandes.objects.all().exclude(state=3)
        #print(waiting_line)
        if(waiting_line):
            try:
                print(f"Platos en lista de espera: {waiting_line[0].plate}")
                comm = f"{waiting_line[0].plate};{waiting_line[0].pk}"
                #print(comm)
                server_ip = "192.168.1.32"
                server_port = 333
                kitchen = socket.socket()
                #print(kitchen)
                kitchen.connect((server_ip, server_port))
                kitchen.send(str.encode(comm))
                kitchen.close()
                return redirect("home")
            except Exception as e:
                return HttpResponse(e)

        else:
            comm = f"Push to receive ;00"
            #print(comm)
            server_ip = "192.168.1.32"
            server_port = 333
            kitchen = socket.socket()
            #print(kitchen)
            kitchen.connect((server_ip, server_port))
            kitchen.send(str.encode(comm))
            kitchen.close()
            data = {"data":"buena"}
            #print(commande)
            return JsonResponse(data)
    else:
        commande_ = Commandes.objects.get(pk=commande)
        commande_.state = 3
        commande_.save()
        commande_pret(commande_)

        time.sleep(5)
        waiting_line = Commandes.objects.all().exclude(state=3)
        #print(waiting_line)
        if(waiting_line):
            try:
                print(f"Platos en lista de espera: {waiting_line[0].plate}")
                comm = f"{waiting_line[0].plate};{waiting_line[0].pk}"
                #print(comm)
                server_ip = "192.168.1.32"
                server_port = 333
                kitchen = socket.socket()
                #print(kitchen)
                kitchen.connect((server_ip, server_port))
                kitchen.send(str.encode(comm))
                kitchen.close()
                return redirect("home")
            except Exception as e:
                return HttpResponse(e)

        else:
            comm = f"Push to receive ;00"
            #print(comm)
            server_ip = "192.168.1.32"
            server_port = 333
            kitchen = socket.socket()
            #print(kitchen)
            kitchen.connect((server_ip, server_port))
            kitchen.send(str.encode(comm))
            kitchen.close()
            data = {"data":"buena"}
            #print(commande)
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

