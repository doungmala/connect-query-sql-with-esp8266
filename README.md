การดึงข้อมูล (Query) จากบอร์ด ESP8266 มักใช้งานร่วมกับเซิร์ฟเวอร์ผ่าน HTTP Request (POST สำหรับบันทึก และ GET สำหรับดึงข้อมูล) ผ่าน ESP8266 NodeMCU HTTP GET and HTTP POST with Arduino IDE และฐานข้อมูล MySQL ESP32/ESP8266 Insert Data into MySQL Database

1. ภาพรวมการทำงาน

• Query (GET): ESP8266 ส่งคำขอแบบ GET ไปยังเซิร์ฟเวอร์ เพื่อดึงข้อมูลหรือสถานะกลับมาแสดงผลหรือควบคุมอุปกรณ์

Setup :

const char* ssid     = "";

const char* password = "";

byte mac_addr[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };

IPAddress server_addr(119,59,100,54);  // IP ของ MySQL server

char dbuser[] = "";         // MySQL username

char dbpassword[] = "";       // MySQL password

// SELECT query (เงื่อนไขในการ Query ข้อมูล)

char query[] = "SELECT * FROM nextsoft_dev_01.esp8266_Floor8_curr ORDER BY id DESC LIMIT 1";  //กำหนดชื่อฐานข้อมูลและชื่อตาราง  DBName.TableName

char query2[] = "SELECT * FROM nextsoft_dev_01.esp8266_Floor8_downto7 ORDER BY id DESC LIMIT 1";

char query3[] = "SELECT * FROM nextsoft_dev_01.esp8266_Floor8_upto9 ORDER BY id DESC LIMIT 1";

ดึงข้อมูลจาก database

MySQL_Cursor *cur_mem = new MySQL_Cursor(&conn);

  //Serial.println(cur_mem);
  
  cur_mem->execute(query); // Execute the query

  column_names *columns = cur_mem->get_columns(); // Fetch the columns

  //Serial.println(columns);
  
  // Read the row (we are only expecting the one)
  
  do {
   
    row = cur_mem->get_next_row();
    
    if (row != NULL) {
     
      Serial.println("......row.......");
     
      Serial.println(row->values[1]); //ค่าที่ SELECT ได้จากฐานข้อมูล
      
      Floor8_curr = atof(row->values[1]);
      
      Serial.println("......Floor8_curr.......");
      
      Serial.println(Floor8_curr);
    
    }
    
  } while (row != NULL);
  
  delete cur_mem;  


*****************************************************************************

ช่องทางติดต่อ:

ชื่อ : ภาธสุ ดวงมาลา

ตำแหน่ง : R&D Manager

Tel : 0641900551

E-mail : nextsoftware.pp@gmail.com

Line : https://lin.ee/THH8PAt

บริษัท เน็กซ์ ซอฟต์แวร์ จำกัด 

ที่อยู่ หมู่บ้าน inizio เลขที่ 888/257 ถนนมะลิวัลย์ ตำบลบ้านทุ่ม อำเภอเมืองขอนแก่น จังหวัดขอนแก่น 40000 เลขที่ผู้เสียภาษี : 0405558003118

ผลงานและประวัติการทำงาน

สามารถดูผลงานและประวัติการทำงานได้ที่

AI, Image Processing : https://www.dropbox.com/scl/fi/tskimhifw0hlcdea5e8t8/Next-Software-2026.pdf?rlkey=f26k2b7t69doklzwxyx54qsmh&dl=0

IoT : https://www.dropbox.com/scl/fi/a5mj4ucjotjv4xrh6sh9q/NS_IOT2025.pdf?rlkey=t0cwl0l4b81w73do2drhqqjp0&dl=0

SEO, Website : https://www.dropbox.com/scl/fi/4q811q0s88xtd8usf5e25/WEB-DEVELOPER-SEARCH-ENGINE-OPTIMIZATION.pdf?rlkey=nvqvndrxv7v9yrfmlcgtplmtx&dl=0
