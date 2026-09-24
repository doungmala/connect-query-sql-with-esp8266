#include <ESP8266WiFi.h>
#include <MySQL_Connection.h>
#include <MySQL_Cursor.h>


const char* ssid     = "Charn_Issara_Parking_8";
const char* password = "nextsoftware888";

byte mac_addr[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
//119.59.100.54
IPAddress server_addr(119,59,100,54);  // IP ของ MySQL server
char dbuser[] = "";         // MySQL username
char dbpassword[] = "";       // MySQL password

// SELECT query (เงื่อนไขในการ Query ข้อมูล)
char query[] = "SELECT * FROM nextsoft_dev_01.esp8266_Floor8_curr ORDER BY id DESC LIMIT 1";  //กำหนดชื่อฐานข้อมูลและชื่อตาราง  DBName.TableName
char query2[] = "SELECT * FROM nextsoft_dev_01.esp8266_Floor8_downto7 ORDER BY id DESC LIMIT 1";
char query3[] = "SELECT * FROM nextsoft_dev_01.esp8266_Floor8_upto9 ORDER BY id DESC LIMIT 1";


WiFiClient client;    
MySQL_Connection conn((Client *)&client);

void setup() {
  Serial.begin(9600);
  delay(10);

  // Connect to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
      delay(100);
      Serial.print(".");
    }

  Serial.println("");
  Serial.print("WiFi connected to ");
  Serial.print("IP : ");
  Serial.println(WiFi.localIP());
  Serial.println("Your device is now online to internet.");
  Serial.println("");

 //MySQL Connection
  Serial.println("Connecting...");
  if (conn.connect(server_addr, 3306, dbuser, dbpassword)) {
    delay(100);
    Serial.println("MySQL Connected.");
  }
  else
    Serial.println("Connection failed.");
  //conn.close();
  delay(10);
  
}

void loop() {
  row_values *row = NULL;
  int Floor8_curr = 0;
  //String head_count ; 
  delay(100);
  
  Serial.println("Selecting data.");

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
  delete cur_mem;  // Deleting the cursor also frees up memory used

  ////////////////////////////////////////////////
  row_values *row2 = NULL;
  int Floor8_downto7 = 0;
  //String head_count ; 
  delay(100);
  
  Serial.println("Selecting data.");

  MySQL_Cursor *cur_mem2 = new MySQL_Cursor(&conn);
  //Serial.println(cur_mem);
  
  cur_mem2->execute(query2); // Execute the query

  column_names *columns2 = cur_mem2->get_columns(); // Fetch the columns

  //Serial.println(columns);
  // Read the row (we are only expecting the one)
  do {
    row2 = cur_mem2->get_next_row();
    
    if (row2 != NULL) {
      Serial.println("......row.......");
      Serial.println(row2->values[1]); //ค่าที่ SELECT ได้จากฐานข้อมูล
      Floor8_downto7 = atof(row2->values[1]);
      Serial.println("......Floor8_downto7.......");
      Serial.println(Floor8_downto7);

    }
  } while (row2 != NULL);
  delete cur_mem2;  // Deleting the cursor also frees up memory used

  
  ////////////////////////////////////////////////
  row_values *row3 = NULL;
  int Floor8_upto9 = 0;
  //String head_count ; 
  delay(100);
  
  Serial.println("Selecting data.");

  MySQL_Cursor *cur_mem3 = new MySQL_Cursor(&conn);
  //Serial.println(cur_mem);
  
  cur_mem3->execute(query3); // Execute the query

  column_names *columns3 = cur_mem3->get_columns(); // Fetch the columns

  //Serial.println(columns);
  // Read the row (we are only expecting the one)
  do {
    row3 = cur_mem3->get_next_row();
    
    if (row3 != NULL) {
      Serial.println("......row.......");
      Serial.println(row3->values[1]); //ค่าที่ SELECT ได้จากฐานข้อมูล
      Floor8_upto9 = atof(row3->values[1]);
      Serial.println("......Floor8_upto9.......");
      Serial.println(Floor8_upto9);

      int Floor8 = Floor8_curr-Floor8_downto7-Floor8_upto9;
      String Floor8_T = String(Floor8);
      Serial.println("......Floor8_T.......");
      Serial.println(Floor8_T);
       
      
    }
  } while (row3 != NULL);
  delete cur_mem3;  // Deleting the cursor also frees up memory used
  
}
