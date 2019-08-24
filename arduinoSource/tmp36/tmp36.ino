int voltage;
int Temperatura;
int TempSenzor = A0;

#define aref_voltage 3.3
float temp[10] = { 0 };

float i = 0;
int n = 0;
float median = 0;

void setup() {
  pinMode(TempSenzor, INPUT);                        //postavi izvod TempSenzor (A0) kao ulazni
  analogReference(EXTERNAL);
  Serial.begin(19200);
}
void loop()
{
  for (int i = 0; i<10; i++)
  {
    float voltage = analogRead(TempSenzor) * 3.3;  //očitava vrijednosti izvoda (A0)
    voltage /= 1024.0;
    float Temperatura = (voltage - 0.5) * 100;
    temp[i] = Temperatura;
    /*Serial.print("Trenutno: ");
    Serial.println(Temperatura);
    */
    delay(10);                                         //čekaj 500 milisekundi
  }
  Array_sort(temp, n);
  median = Find_median(temp, n);
  Serial.print("Filtrirano: ");
  Serial.println(median);
}

// function to sort the array in ascending order
void Array_sort(float *array, int n)
{
  // declare some local variables
  int i = 0, j = 0, temp = 0;

  for (i = 0; i<n; i++)
  {
    for (j = 0; j<n - 1; j++)
    {
      if (array[j]>array[j + 1])
      {
        temp = array[j];
        array[j] = array[j + 1];
        array[j + 1] = temp;
      }
    }
  }
}

float Find_median(float array[], int n)
{
  float median = 0;

  // if number of elements are even
  if (n % 2 == 0)
    median = (array[(n - 1) / 2] + array[n / 2]) / 2.0;
  // if number of elements are odd
  else
    median = array[n / 2];

  return median;
}
