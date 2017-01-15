void countdown() {
  digitalWrite(targetOneLive, HIGH);
  digitalWrite(targetTwoLive, HIGH);
  digitalWrite(targetHit, HIGH);
  digitalWrite(targetMiss, HIGH);
  delay(1000);
  digitalWrite(targetOneLive, LOW);
  delay(1000);
  digitalWrite(targetTwoLive, LOW);
  delay(1000);
  digitalWrite(targetMiss, LOW);
  delay(1000);
  digitalWrite(targetHit, LOW);
  delay(1000);
}

