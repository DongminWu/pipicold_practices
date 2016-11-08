import requests
import string
import time

HON_SHOWUNIT_WEBSITE = "http://87.106.84.161/hon/whm_showunit.php"
HON_NO_ROOM_PROMOTE="Es wurden keine Ergebnisse zu ihrer Anfrage gefunden."


def request_hon_website (start_date,start_month,start_year, 
        end_date, end_month, end_year, hometype):
    #initialization
    post_data={
            "start_tag"     :"Anfang",
            "start_monat"   :"11",
            "start_jahr"    :"2016",
            "end_tag"       :"Mitte",
            "end_monat"     :"08",
            "end_jahr"      :"2017",
            "datum"         :"01.11.2016",
            "uhrzeit"       :"13%3A00",
            "typ[]"         :["0","1","2","3"],
            "absenden"      :"%C2%A0%C2%A0Next%C2%A0%C2%A0"
            };



    #autofilling the start and end tag

    if (start_date <= 0):
        return 1,"ErrorDate"
    elif (start_date >=1 and start_date <= 15):
        post_data["start_tag"] = "Anfang"
    elif (start_date >=16 and start_date <=31):
        post_data["start_tag"] = "Mitte"
    elif (start_date >= 31):
        return 1,"ErrorDate"

    if (end_date <= 0):
        return 1,"ErrorDate"
    elif (end_date >=1 and end_date <= 15):
        post_data["end_tag"] = "Mitte"
    elif (end_date >=16 and end_date <=31):
        post_data["end_tag"] = "Ende"
    elif (end_date >= 31):
        return 1,"ErrorDate"


    if (start_year > end_year):
        return 1,"ErrorDate"
    elif (start_year == end_year and start_month <= end_month):
        return 1,"ErrorDate"


    post_data["start_monat"]    = "%02d" % (start_month)
    post_data["start_jahr"]     = "%04d" % (start_year)
        
    post_data["end_monat"]      = "%02d" % (end_month)
    post_data["end_jahr"]       = "%04d" % (end_year)


    post_data["datum"]          = "%02d.%02d.%04d" % (start_date,start_month,start_year)

    post_data["typ[]"]          = hometype

    #print "post_data:", post_data
    
    try:
        ret = requests.post(HON_SHOWUNIT_WEBSITE,post_data)
    except:
        print "catched excpetions"
    else:
        print "go !"
    if (ret.url != HON_SHOWUNIT_WEBSITE):
        return 2,"ErrorHON"
    return 0,ret.text




def hon_room_check(start_date,start_month,start_year, 
        end_date, end_month, end_year, hometype):

    print "checking room from %02d.%02d.%04d" % (start_date,start_month, start_year)
    err, content =request_hon_website(start_date,start_month,start_year, end_date, end_month, end_year, hometype)


    if (err != 0):
        print content;
        return 1
    else:
        print "fetch data successful!"
        ret = content.rfind(HON_NO_ROOM_PROMOTE,0,len(content));
        if (ret == -1):
            print ">>>>>>>>>>>>>>>>>>>>>>>Find room:", hometype
            return 2
        else:
            print "No room:", hometype
            return 0
    return 0



def send_email(subject,content):
    account="wdm228@126.com"
    password="Goaway126"
    sendto="wdm228@qq.com"
    smtp_server_addr="smtp.126.com"
    smtp_server_port=25


    from email import encoders
    from email.header import Header
    from email.mime.text import MIMEText
    from email.utils import parseaddr, formataddr
    import smtplib

    def _format_addr(s):
        name, addr = parseaddr(s)
        return formataddr(( \
            Header(name, 'utf-8').encode(), \
            addr.encode('utf-8') if isinstance(addr, unicode) else addr))


    msg = MIMEText(content, 'plain', 'utf-8')
    msg['From'] = _format_addr('HON querying <%s>' % account)
    msg['To'] = _format_addr('homeless <%s>' % sendto)
    msg['Subject'] = Header(subject, 'utf-8').encode()
    
    import smtplib
    print "smtp connecting"
    server = smtplib.SMTP(smtp_server_addr, smtp_server_port)
    print "smtp connected"
    server.starttls()
    print "starttls finished"
    server.set_debuglevel(1)
    server.login(account, password)
    server.sendmail(account, [sendto], msg.as_string())
    server.quit()
    return 0;
    
    

if __name__ == '__main__':
    print "hello"
    task_table={
            "task1":0,
            "task2":0,
            "task3":0,
            "task4":0,
            }
    last_heart_time=time.time()
    
    last_time=0
    while(1):
        if ( time.time() - last_time > 30):
            print ""
            print ""
            task1_err=hon_room_check(11,11,2016,30,8,2017,['0','1'])
            task2_err=hon_room_check(11,11,2016,30,8,2017,['2','3'])
            if (task1_err == 2):
                print "finded room!"
                if ((time.time() - task_table["task1"]) > 2000):
                    send_email("finded 11.1 sigle room/ap",("@%d, yoyoyoyo %s" % (time.time(),HON_SHOWUNIT_WEBSITE)))
                    task_table["task1"]=time.time()
            if (task2_err == 2):
                print "finded room!"
                if ((time.time() - task_table["task2"]) > 2000):
                    send_email("finded 11.1 DAAAAAA",("@%d lalla %s" % (time.time(),HON_SHOWUNIT_WEBSITE)))
                    task_table["task2"]=time.time()




            task3_err=hon_room_check(16,11,2016,30,8,2017,['0','1'])
            task4_err=hon_room_check(16,11,2016,30,8,2017,['2','3'])
            if (task3_err == 2):
                print "finded room!"
                if ((time.time() - task_table["task3"]) > 2000):
                    #send_email("finded 11.16 sigle room/ap",("@%d, yoyoyoyo %s" % (time.time(),HON_SHOWUNIT_WEBSITE)))
                    task_table["task3"]=time.time()
            if (task4_err == 2):
                print "finded room!"
                if ((time.time() - task_table["task4"]) > 2000):
                    send_email("finded 11.16 DAAAAAA",("@%d lakkklla %s" % (time.time(),HON_SHOWUNIT_WEBSITE)))
                    task_table["task4"]=time.time()

            if (time.time()-last_heart_time > 60*60*2):
                send_email("beats heart!",HON_SHOWUNIT_WEBSITE)
                last_heart_time = time.time()

            last_time=time.time()

        
        
    print "end"

