int main ()
{
  char *video = (char *)0xB8000;
  char *hello = "Hello World";
  for (int i = 0; i < 11; i++)
    {
      video[0] = hello[i];
      video += 2;
    }
}
