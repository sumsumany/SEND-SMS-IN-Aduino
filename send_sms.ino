const int switchPin = 3;     // 스위치에 연결된 핀 번호 설정

void setup() {
  Serial2.begin(115200);          // 시리얼 통신 초기화
  pinMode(switchPin, INPUT_PULLUP);    // 스위치 핀을 입력 모드로 설정하고 내부 풀업 저항 사용
  delay(1000);
}

void loop() {
  if (digitalRead(switchPin) == 0) {
    sendSMS("01012345678", "Switch pressed!");  // 스위치 누를 때 SMS 전송 함수 호출
    delay(1000);  // 디바운싱을 위한 딜레이
  }
}

void sendSMS(String phoneNumber, String message) {
  Serial2.println("AT+CMGF=1");    // SMS 모드로 설정
  delay(1000);
  Serial2.print("AT+CMGS=\"");
  Serial2.print(phoneNumber);     // 수신자 전화번호 설정
  Serial2.println("\"");
  delay(1000);
  
  Serial2.print(message);          // 메시지 내용 설정
  delay(1000);
  
  Serial2.write(0x1A);               // Ctrl+Z 문자 전송 (메시지 보내기)
  delay(1000);
  
  // 전송 결과 확인
  while (Serial2.available()) {
    Serial2.write(Serial2.read());
  }
}