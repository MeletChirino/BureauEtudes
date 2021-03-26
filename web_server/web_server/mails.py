#!/usr/bin/env python
# -*- coding: utf-8 -*-
#Email Modules
from email.mime.text import MIMEText
from email.message import EmailMessage

#Django
from django.utils.encoding import smart_str
from django.template import Template, Context

#PythonModules
import smtplib
import os
import json

def commande_pret(commande):
    print("Enviando Correo")

    with open('/etc/config.json') as config_file:
        config = json.load(config_file)

    server = smtplib.SMTP('smtp.gmail.com', 587)
    server.ehlo()
    server.starttls()
    server.ehlo()

    server.login(config['EMAIL_USER'],
            config['EMAIL_PASSWORD']
            )
    subject = 'Comande Pret'
    plate_name = commande.plate.name[:-2]
    plate_name.strip()
    body = f"Votre commande de {plate_name} numero {commande.pk} est pret a retirer\n\nAvec amour,\nVotre RU Prefere..."
    #msg = f'Subject: {subject}\n\n{body}'
    msg = EmailMessage()
    msg['Subject'] = subject
    msg['From'] = 'RU UT3'
    msg['To'] = commande.email
    msg.set_content(body)
    server.send_message(msg)
