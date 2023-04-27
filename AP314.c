#include <stdio.h>
#include <stdlib.h>


void question1b(void);
void question2(void);
int rbe(int base, int exponent, int rem);
int ExtendedEuclidsAlg(int r1, int r2);
int *ExtendedEuclidsAlgMod(int r1, int r2);
int EuclidsAlgorithmGCD(int a, int b);
int swap(int *a, int *b);
int *convertNum(char *a);
char *convertChar(int *a, int size);
int EulerTotientFunction(int p, int q);
void printTable(void);

int main(int argc, char* argv[]) {

  //question1b();
  question2();
  return 0;
}

void question2(void)
{
  int *temp;
  int prime1 = 17;
  int prime2 = 41;
  int modulus = prime1*prime2;

  printf("We start by assuming Alice and Bob wants to send each other messages\n");
  printf("and will be encrypting their messages with RSA encryption.\n");
  printf("Their public key pairs are:\n");
  printf("Alice(%d, %d),\t Bob(%d, %d).\n\n", prime1, modulus, prime2, modulus);
  printf("However Karen enters the picture with a devious plan.\n");
  printf("She wishes to decrypt their messages by means of a Common Modulus Attack.\n\n");

  printf("A fourth person Dennis sends an encrypted message to both Alice and Bob with\n");
  printf("their different but unique encryption keys. Karen intercepts these messages\n");
  printf("and made use of the following steps to decrypt the message.\n\n");

  printf("The two encrypting exponents are %d, and %d.\n\n", prime1, prime2);
  int test = EuclidsAlgorithmGCD(prime1, prime2);
  printf("We see these esponents' greatest common divisor is: %d.\n\n", test);

  int totient = EulerTotientFunction(prime1, prime2);
  printf("To test the validity of these exponents we use the totient function\n");
  printf("of %d and get %d. With this we get their respective\n", modulus, totient);
  printf("Greatest Common Divisor with the two exponents.\n\n");

  int res1 = EuclidsAlgorithmGCD(totient, prime1);
  printf("The Greatest Common divisor is: %d\n", res1);
  printf("Thus the encrypting exponent for Alice is %d.\n\n", prime1);

  int res2 = EuclidsAlgorithmGCD(totient, prime2);
  printf("The Greatest Common divisor is: %d\n", res2);
  printf("Thus the encrypting exponent for Bob is %d.\n\n\n", prime2);

  

  printf("We get the inverses of %d and %d so we can\n", prime1, prime2);
  printf("satisfy the equation: a*e1 + b*e2 = 1.\n");
  printf("With e1 and e2 being the public key exponents and\n");
  printf("a and b being their inverses respectively.\n\n");
  temp = ExtendedEuclidsAlgMod(prime1, prime2);
  int a = temp[0];
  int b = temp[1];

  printf("a=%d  b=%d\n", a, b);
  printf("a*e1 + b*e2 = 1 \n=> %d*%d + %d*%d = %d\n\n\n", a, prime1, b, prime2,
   a*prime1 + b*prime2);

  
  int size = 12;
  char message[12] = "MEET AT NINE";

  printf("Dennis now sends the messsage:\n%s\n", message);
  printf("to Alice and Bob respectively.\n\n");

  printf("Converting letters to numbers we use the following table:\n");
  printTable();

  printf("Converting the letters to numbers we get:\n\n");
  int *MsgNum = convertNum(message);
  for (int i = 0; i < size; i++) {
    printf("%d;", MsgNum[i]);
  }
  printf("\n\n");
  printf("As our unencrypted message.\n\n");

  printf("Dennis now use the encrypting exponent for Alice by the following:\n\n");

  int *encryptedMsg1 = malloc(size*sizeof(int));
  for (int i = 0; i < size; i++) {
    encryptedMsg1[i] = rbe(MsgNum[i], prime1, modulus);
  }
  printf("Dennis follows by using the encrypting exponent for Bob by the following:\n\n");

  int *encryptedMsg2 = malloc(size*sizeof(int));
  for (int i = 0; i < size; i++) {
    encryptedMsg2[i] = rbe(MsgNum[i], prime2, modulus);
  }

  printf("Thus we get the encrypted message Dennis sends to Alice as:\n");
  for (int i = 0; i < size; i++) {
    printf("%d;", encryptedMsg1[i]);
  }
  printf("\n\nAnd we get the encrypted message Dennis sends to Bob as:\n");
  for (int i = 0; i < size; i++) {
    printf("%d;", encryptedMsg2[i]);
  }
  printf("\n\n");

  printf("However Karen intercepts both these messages and uses\n");
  printf("the fact that c1^(a)*c2^(b) gives the unencrypted message\n");
  printf("given that c1 and c2 are the encrypted messages sent to\n");
  printf("Alice and Bob respectively.\n\n");

  if (a < 0) {
    printf("Here a < 0, thus we need to change the exponent such that:\n");
    printf("m = c1^(a)*c2^(b) mod N\n");
    printf("m = [c1^(-1)]^(|a|)*c2^(b) mod N\n\n");
    printf("Therefore we need to get: c1^(-1) before we may continue\n");
    printf("at each step.\n\n");
  } else if (b < 0) {
    printf("Here b < 0, thus we need to change the exponent such that:\n");
    printf("m = c1^(a)*c2^(b) mod N\n");
    printf("m = c1^(a)*[c2^(-1)]^(|b|) mod N\n\n");
    printf("Therefore we need to get: c2^(-1) before we may continue\n");
    printf("at each step.\n\n");
  }

  printf("Now Karen uses the Extended Euclids algorithm if necessary,\n");
  printf("as well as the Square-multiply algorithm to calculate:\n");
  printf("m = c1^(a)*c2^(b) mod N\n");
  printf("for each number.\n\n");


  int *decryptedMsg = malloc(size*sizeof(int));
  for (int i = 0; i < size; i++) {
    int tempA = 1, tempB = 1;
    if (a < 0) {
      tempA = ExtendedEuclidsAlg(modulus, encryptedMsg1[i]);
      printf("We now have %d^(-1) = %d\n\n", encryptedMsg1[i], tempA);
      decryptedMsg[i] = rbe(tempA, abs(a), modulus);
      decryptedMsg[i]*= rbe(encryptedMsg2[i], b, modulus);

      decryptedMsg[i] = decryptedMsg[i] % modulus;
      printf("Thus we have that:\n[%d^(-1)]^(%d)*%d^(%d) = %d\n\n",
        encryptedMsg1[i], abs(a), encryptedMsg2[i], b, decryptedMsg[i]);
    }
    else if (b < 0) {
      tempB = ExtendedEuclidsAlg(modulus, encryptedMsg2[i]);
      printf("We now have %d^(-1) = %d\n\n", encryptedMsg2[i], tempB);
      decryptedMsg[i] = rbe(encryptedMsg1[i], a, modulus);
      decryptedMsg[i]*= rbe(tempB, abs(b), modulus);

      decryptedMsg[i] = decryptedMsg[i] % modulus;
      printf("Thus we have that:\n%d^(%d)*[%d^(-1)]^(%d) = %d\n\n",
        encryptedMsg1[i], a, encryptedMsg2[i], abs(b), decryptedMsg[i]);
    } else {
      decryptedMsg[i] = rbe(encryptedMsg1[i], a, modulus);
      decryptedMsg[i]*= rbe(encryptedMsg2[i], b, modulus);

      decryptedMsg[i] = decryptedMsg[i] % modulus;
      printf("Thus we have that:\n%d^(%d)*%d^(%d) = %d\n\n",
        encryptedMsg1[i], a, encryptedMsg2[i], b, decryptedMsg[i]);
    }   
  }

  printf("\nNow that Karen has gone through all that effort she gets the\n");
  printf("unencrypted message:\n\n");
  for (int i = 0; i < size; i++) {
    printf("%d;", decryptedMsg[i]);
  }
  printf("\n\n");

  printf("By using the table:\n");
  printTable();

  printf("She swiftly converts these numbers to:\n");

  char *recvMsg = convertChar(decryptedMsg, size);
  for (int i = 0; i < size; i++) {
    printf("%c", recvMsg[i]);
  }
  printf("\n\n");
  printf("Now Karen knows what Alice and Bob are going to meet\n");
  printf("Dennis at 9.\n");

  free(temp);
  free(MsgNum);
  free(recvMsg);
  free(decryptedMsg);
  free(encryptedMsg1);
  free(encryptedMsg2);

  printf("References:\n");
  printf("https://youtu.be/uX2z4fZYYkQ");
  printf("\n");
}

void question1b(void)
{
  int prime1 = 31;
  int prime2 = 47;
  int n = prime1*prime2;

  printf("We start by assuming that Alice chose the encrypting exponent");
  printf(" %d\n", prime1);
  printf("And Bob chose the encrypting exponent %d.\n\n", prime2);
  
  printf("These primes are multiplied to obtain the RSA key: %d\n", n);
  printf("To calculate a 'universal' encryption exponent we need to obtain the\n");
  printf("totient function number.\n\n");

  int totient = EulerTotientFunction(prime1, prime2);
  printf("The totient function is calculated to be: %d\n\n", totient);

  int e = 43;
  printf("Now we choose a encryption exponent %d.\n", e);
  printf("To verify whether this number can be used as a valid encryption key, \n");
  printf("we calculate the greatest commen divisor of 'e' and the totient number.\n\n");

  int res = EuclidsAlgorithmGCD(totient, e);
  printf("The Greatest Common divisor is: %d\n", res);
  printf("Thus the encrypting exponent %d, is valid.\n\n", e);

  printf("To obtain the decryption key we perform the\n");
  printf("Extended Euclid's algorithm\n\n");
  int d = ExtendedEuclidsAlg(totient, e);
  printf("Thus the decryprion exponent is: %d\n\n", d);

  

  int size = 12;
  char message[12] = "MEET AT NINE";
  printf("Alice wants to send the message:\n%s\n", message);
  printf("to Bob.\n\n");

  printf("To convert the letters to numbers, she uses the following table.\n");
  printTable();

  int *sendMsg = convertNum(message);
  printf("Using the table, this message is converted into the number:\n");

  for (int i = 0; i < size; i++) {
    printf("%d;", sendMsg[i]);
  }
  printf("\n\n");

  printf("We now proceed to perform the Square-multiply algorithm on every\n");
  printf("number to obtain the encrypted message.\n\n");

  int *encryptedMsg = malloc(size*sizeof(int));
  for (int i = 0; i < size; i++) {
    encryptedMsg[i] = rbe(sendMsg[i], e, n);
  }
  
  printf("It concludes that the encrypted message Bob receives are:\n");
  for (int i = 0; i < size; i++) {
    printf("%d;", encryptedMsg[i]);
  }
  printf("\n\n");

  printf("Bob wants to decrypt the message with decrypting exponent: %d\n\n", d);

  printf("We now proceed to once again perform the Square-multiply algorithm on\n");
  printf("every number to obtain the decrypted message.\n\n");
  
  int *decryptedMsg = malloc(size*sizeof(int));
  for (int i = 0; i < size; i++) {
    decryptedMsg[i] = rbe(encryptedMsg[i], d, n);
  }

  printf("It concludes that the decrypted message Bob calculated are:\n");
  for (int i = 0; i < size; i++) {
    printf("%d;", decryptedMsg[i]);
  }
  printf("\n\n");

  printf("By using the table.\n");
  printTable();

  printf("We finally convert these number back using the table.\n");
  char * recvMsg = convertChar(decryptedMsg, size);
  for (int i = 0; i < size; i++) {
    printf("%c", recvMsg[i]);
  }
  printf("\n\n");

  printf("Bob has now successfully decrypted the message that Alice\n");
  printf("has encrypted.\n\n");
  printf("Alice used the public key (%d, %d).\n", e, n);
  printf("Bob used the private key d: %d\n", d);
  printf("They used these keys to securely send a message from Alice to Bob.\n");

  free(sendMsg);
  free(recvMsg);
  free(encryptedMsg);
  free(decryptedMsg);
}

int rbe(int base, int exponent, int rem) {
  int r = 1;
  printf("Square-multiply algorithm\nfor:%d^%d(mod %d)\n",
    base, exponent, rem);
  printf("-------------------------\n");
  printf("|r\t|b\t|e\t|\n");
  printf("-------------------------\n");
  printf("|%d\t|%d\t|%d\t|\n", r, base, exponent);
  while (exponent > 0) {
    if (exponent % 2 == 1) {
      r = (r * base) % rem;
    }
    base = (base*base) % rem;
    exponent = exponent / 2;
    printf("|%d\t|%d\t|%d\t|\n", r, base, exponent);
  }
  printf("-------------------------\n\n");
  return r;
}

int ExtendedEuclidsAlg(int r1, int r2){
  int i = 0;
  int x1 = 1, x2 = 0;
  int y1 = 0, y2 = 1;
  int q;
  if (r1 < r2) {
    swap(&r1, &r2);
  }
  int n = r1;
  printf("Extended Euclid's algorithm for:GCD(%d, %d)\n",
    r1, r2);
  printf("In the form: %dx + %dy = r\n", r1, r2);
  printf("-----------------------------------------\n");
  printf("|i\t|q\t|r\t|x\t|y\t|\n");
  printf("-----------------------------------------\n");
  printf("|%d\t|-\t|%d\t|%d\t|%d\t|\n", i++, r1, x1, y1);
  printf("|%d\t|-\t|%d\t|%d\t|%d\t|\n", i++, r2, x2, y2);

  while (r2 > 0) {
    q = r1/r2;

    r1 = r1 - q*r2;
    swap(&r1, &r2);

    x1 = x1 - q*x2;
    swap(&x1, &x2);

    y1 = y1 - q*y2;
    swap(&y1, &y2);

    printf("|%d\t|%d\t|%d\t|%d\t|%d\t|\n", i++, q, r2, x2, y2);
  }
  printf("-----------------------------------------\n\n");
  if (y1 < 0) {
    y1 = n + y1;
  }
  return y1;
}
int *ExtendedEuclidsAlgMod(int r1, int r2)
{
  int i = 0, prev = 0;
  int x1 = 1, x2 = 0;
  int y1 = 0, y2 = 1;
  int q;
  int *ret;
  if (r1 < r2) {
    swap(&r1, &r2);
  }
  printf("Extended Euclid's algorithm for:GCD(%d, %d)\n",
    r1, r2);
  printf("In the form: %dx + %dy = r\n", r1, r2);
  printf("-----------------------------------------\n");
  printf("|i\t|q\t|r\t|x\t|y\t|\n");
  printf("-----------------------------------------\n");
  printf("|%d\t|-\t|%d\t|%d\t|%d\t|\n", i++, r1, x1, y1);
  printf("|%d\t|-\t|%d\t|%d\t|%d\t|\n", i++, r2, x2, y2);

  while (r2 > 0) {
    q = r1/r2;

    r1 = r1 - q*r2;
    swap(&r1, &r2);

    x1 = x1 - q*x2;
    swap(&x1, &x2);

    prev = y1;
    y1 = y1 - q*y2;
    swap(&y1, &y2);

    printf("|%d\t|%d\t|%d\t|%d\t|%d\t|\n", i++, q, r2, x2, y2);
  }
  printf("-----------------------------------------\n\n");
  
  ret  = malloc(2*sizeof(int));
  ret[0] = y1;
  ret[1] = prev;
  return ret;
}
int EuclidsAlgorithmGCD(int a, int b) {
  if (a < b) {
    swap(&a, &b);
  }
  printf("Euclid's Algorithm for computing GCD\n");
  printf("GCD(%d, %d)\n", a, b);
  printf("---------------------------------\n");
  printf("|a\t|b\t|a(mod b) = r\t|\n");
  printf("---------------------------------\n");
  while (b > 0) {
    int temp = a % b;
    printf("|%d\t|%d\t|%d\t\t|\n", a, b, temp);
    a = temp;
    swap(&a, &b);
  }
  printf("|%d\t|%d\t|\t\t|\n", a, b);
  printf("---------------------------------\n\n");
  return a;
}
int swap(int *a, int *b) {
  int temp = *a;
  *a = *b;
  *b = temp;
}
int *convertNum(char *a){
  char chars[28] = {"-BCDEFGHIJKLMNOPQRSTUVWXYZ A"};
  int size = 0;
  while (a[size] != '\0') size++;
  int *sendMsg = malloc(size*sizeof(int) - 1);

  for (int i=0; i < size; i++) {
    for (int j = 0; j < 28; j++) {
      if (a[i] == chars[j]) {
        sendMsg[i] = j;
      }
    }
  }
  return sendMsg;
}

char *convertChar(int *a, int size) {
  char chars[28] = {"-BCDEFGHIJKLMNOPQRSTUVWXYZ A"};
  char * recvMsg = malloc(size*sizeof(int) -1);
  for (int i = 0; i < size; i++) {
    recvMsg[i] = chars[a[i]];
  }
  return recvMsg;
}

int EulerTotientFunction(int p, int q) {
  return (p-1)*(q-1);
}

void printTable(void)
{
  char chars[28] = {"-BCDEFGHIJKLMNOPQRSTUVWXYZ A"};
  printf("\n");
  printf("-----------------------------------\n");
  printf("|Character|Number|Character|Number|\n");
  printf("-----------------------------------\n");
  for (int i = 0; i < 14; i++) {
    printf("|%c\t  |%d\t |", chars[i], i);
    printf("%c\t   |%d\t  |\n", chars[i+14], i+14);
  }
  //printf("|\t  |\t |");
  //printf("' '\t   |26\t  |\n");
  printf("-----------------------------------\n\n");
}
