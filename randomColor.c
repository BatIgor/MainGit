int white[3]  = { 100, 100, 100 };
int red[3]    = { 100, 0, 0 };
int green[3]  = { 0, 100, 0 };
int blue[3]   = { 0, 0, 100 };
int yellow[3] = { 40, 95, 0 };
char* colors[] = { "white", "red", "green", "blue", "yellow" };

int newRand = rand()%6;

void loop()
{
  crossFade(colors[newRand]);
  int prevRand = newRand;
  while (newRand == prevRand) {newRand = rand()%6;}
  
  //вот так выглядят команды без всяких рандомов
  //crossFade(red);
  //crossFade(green);
  //crossFade(blue);
  //crossFade(yellow);
  //я пытаюсь сделать так, чтобы он брал случайный цвет из массива цветов,
  //но чтобы этот цвет не повторялся два раза подряд; на 15 строке - ошибка
  //error: cannot convert 'char*' to 'int*' for argument '1' to 'void crossFade(int*)'

}