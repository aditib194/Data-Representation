#include <data.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int convertCharToNumber(char ch)
{
  if (ch >= '0' && ch <= '9')
  {
    return ch - '0';
  }
  else if (ch >= 'A' && ch <= 'F')
  {
    return ch - 'A' + 10;
  }
  else
  {
    return -1;
  }
}

char convertNumberToChar(int n)
{
  if (n >= 0 && n <= 9)
  {
    return n + '0';
  }
  else if (n >= 10 && n <= 15)
  {
    return n - 10 + 'A';
  }
  else
  {
    return 0;
  }
}

Data convert_to_base_n(Data src, unsigned char n)
{
  Data new_data;
  new_data.data = NULL;
  // TODO
  int u = convert_to_int(src);
  //printf("%d", u);
  if(u < 0) {
    //u = ~((int)(pow(2, src.number_bits) + 1e-9) - 1) ^ u;
    u = ~u;
  }
  new_data.base = n;
  new_data.sign = src.sign;
  new_data.len = 0;
  new_data.number_bits = src.number_bits;
  DataNode *next = NULL;
  DataNode *current = NULL;
  if(u != 0) {
    while (u != 0)
    {
      current = malloc(sizeof(struct DataNode));
      current->number = convertNumberToChar(u % n);
      current->next = next;
      next = current;
      u = u / n;
      new_data.len++;
    }
  } else {
    current = malloc(sizeof(struct DataNode));
      current->number = '0';
      current->next = NULL;
      new_data.len++;
  }
  new_data.data = current;
  int x = 1;
  if(new_data.data == NULL) {
    x = 0;
  }
  //printf("%d", x);
  return new_data;
}

int convert_to_int(Data src)
{
  // TODO
  DataNode *head = src.data;
  int c = 0;
  for (int i = src.len - 1; i >= 0; i--)
  {
    c += convertCharToNumber(head->number) * (int)(pow(src.base, i) + 1e-9);
    head = head->next;
  }

  if (src.sign)
  {
    if (c / ((int)(pow(2, src.number_bits - 1) + 1e-9)) == 1)
    {
      c = ~((int)(pow(2, src.number_bits) + 1e-9) - 1) ^ c;
    }
  }
  return c;
}

Data left_shift(Data src, int n)
{
  Data new_data;
  // TODO
  new_data = convert_to_base_n(src, 2);
  DataNode *head = new_data.data;
  while (head->next != NULL)
  {
    head = head->next;
  }
  for (int i = 0; i < n; i++)
  {
    DataNode *next = malloc(sizeof(struct DataNode));
    next->number = '0';
    next->next = NULL;
    head->next = next;
    head = next;
    new_data.len++;
  }

  while(new_data.len > new_data.number_bits)
  {
    DataNode *next_pointer = new_data.data->next;
    free(new_data.data);
    new_data.data = next_pointer;
    new_data.len--;
  }

  while (new_data.data->number != '1' && new_data.data->next != NULL)
  {
    DataNode *next_pointer = new_data.data->next;
    free(new_data.data);
    new_data.data = next_pointer;
    new_data.len--;
  }
  return new_data;
}

Data right_shift(Data src, int n)
{
  Data new_data;
  // TODO
  new_data = convert_to_base_n(src, 2);
  if (new_data.sign && new_data.number_bits == new_data.len)
  {
    if(n < new_data.len) {
      int last = new_data.len - n;
      DataNode *l = new_data.data;
      for (int i = 1; i < last; i++)
      {
        l = l->next;
      }
      l->next = NULL;
    } else if(n == new_data.len) {
      new_data.data->number = '0';
      new_data.len = '1';
    } else {
      new_data.data = NULL;
    }
    int new = n;
    if(n > new_data.len) {
      new = new_data.number_bits;
    }
    for(int i = 0; i < new; i++){
      DataNode *new_node = malloc(sizeof(struct DataNode));
      new_node->number = '1';
      new_node->next = new_data.data;
      new_data.data = new_node;
    }
  }
  else
  {
    if(n < new_data.len) {
      int last = new_data.len - n;
      DataNode *l = new_data.data;
      for (int i = 1; i < last; i++)
      {
        l = l->next;
      }
      l->next = NULL;
      new_data.len = new_data.len - n;
    } else if(n == new_data.len) {
        new_data.data->number = '0';
        new_data.len = '1';
    } else {
      new_data.data = NULL;
      new_data.len == '0';
    }
  }
  return new_data;
}
