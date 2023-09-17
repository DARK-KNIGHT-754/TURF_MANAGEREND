#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


struct Date {
  int day;
  int month;
  int year;
};
struct turf {
  int SID;
  int fee;
  char slot[15];
};
struct Booking {
  int d, m, y;
  char slot[15];
  int fee;
  char cname[20];
  char ph[20];
  char stat[20];
  int bookid;
};

struct Date getCurrentDate() {
  struct Date currentDate;
  time_t t;
  struct tm *tm_info;

  time(&t);
  tm_info = localtime(&t);

  currentDate.day = tm_info->tm_mday;
  currentDate.month = tm_info->tm_mon + 1;
  currentDate.year = tm_info->tm_year + 1900;
  return currentDate;
}

int checkdate(int input_day, int input_month, int input_year) {
  time_t now = time(NULL);
  struct tm *sys_time = localtime(&now);
  int sys_year = sys_time->tm_year + 1900; // adjust year value
  int sys_month = sys_time->tm_mon + 1;    // adjust month value
  int sys_day = sys_time->tm_mday;

  if (input_year > sys_year ||
      (input_year == sys_year && input_month > sys_month) ||
      (input_year == sys_year && input_month == sys_month &&
       input_day > sys_day)) {
    return 1;
  } else if (input_year < sys_year ||
             (input_year == sys_year && input_month < sys_month) ||
             (input_year == sys_year && input_month == sys_month &&
              input_day < sys_day)) {
    return 0;
  } else {
    return 1;
  }
}

void adminwritedata() {
  FILE *f;
  struct turf t;
  f = fopen("turf.dat", "a");
  printf("Enter next Slot ID :");
  scanf("%d", &t.SID);
  printf("Enter the Slot timing :");
  fflush(stdin);
  scanf("%s", t.slot);
  printf("fee of slot is : ");
  scanf("%d", &t.fee);
  fwrite(&t, sizeof(struct turf), 1, f);
  fclose(f);
}

void adminreaddata() {
  FILE *f;
  struct turf t;
  f = fopen("turf.dat", "r");
  while (fread(&t, sizeof(struct turf), 1, f)) {
    printf("\nSID : %d\t slot timing : %s \t fee :%d\n", t.SID, t.slot, t.fee);
  }
  fclose(f);
}

void adminmodifyslots() {
  FILE *f;
  struct turf t;
  int a, flag = 0, pos;
  printf("\nenter SIB for modifying :");
  scanf("%d", &a);
  f = fopen("turf.dat", "r+");
  while (fread(&t, sizeof(struct turf), 1, f)) {
    if (t.SID == a) {
      printf("\nSID : %d\t slot timing : %s \t fee :%d\n", t.SID, t.slot,
             t.fee);
      pos = ftell(f);
      flag = 1;
      break;
    }
  }
  if (flag == 0)
    printf("No such record is found");
  else {
    fseek(f, pos - sizeof(t), SEEK_SET);
    printf("Enter slot:");
    fflush(stdin);
    scanf("%s", t.slot);
    printf("Enter fee:");
    scanf("%d", &t.fee);
    fwrite(&t, sizeof(struct turf), 1, f);
  }
  fclose(f);
}

int profitofday() {
  FILE *f1;
  struct Booking b;
  int d, m, y, flag, profit = 0;
  char ch;
  printf("\nenter date to search (DD/MM/YYYY)");
  scanf("%d/%d/%d", &d, &m, &y);
  f1 = fopen("booking.dat", "r");
  while (fread(&b, sizeof(struct Booking), 1, f1)) {
    if (b.d == d && b.m == m && b.y == y) {
      if (strcmp(b.stat, "booked") == 0) {
        profit = profit + b.fee;
      }
    }
  }
  printf("\nprofit on date (%d/%d/%d) is %d", d, m, y, profit);
  fclose(f1);
}

int profitofmonth() {
  FILE *f1;
  struct Booking b;
  int m, y, flag, profit = 0;
  char ch;
  printf("\nenter month to search (MM/YYYY)");
  scanf("%d/%d", &m, &y);
  f1 = fopen("booking.dat", "r");
  while (fread(&b, sizeof(struct Booking), 1, f1)) {
    if (b.m == m && b.y == y) {
      if (strcmp(b.stat, "booked") == 0) {
        profit = profit + b.fee;
      }
    }
  }
  printf("\nprofit on date (%d/%d) is : %d\n", m, y, profit);
  fclose(f1);
}

void admindeleteslots() {
  FILE *f1, *f2;
  struct turf t;
  f1 = fopen("turf.dat", "r");
  f2 = fopen("temp.dat", "w");
  int a, flag = 0;
  printf("Slot ID for deletion :");
  scanf("%d", &a);
  while (fread(&t, sizeof(struct turf), 1, f1)) {
    if (t.SID != a) {
      fwrite(&t, sizeof(struct turf), 1, f2);
    } else {
      flag = 1;
    }
  }
  fclose(f1);
  fclose(f2);
  if (flag == 0)
    printf("No such record");
  else {
    remove("turf.dat");
    rename("temp.dat", "turf.dat");
    printf("Record is Deleted");
  }
}

void adminmainmenu() {
  int ch;
  do {
    printf("\nAdmin Menu");
    printf("\n1. add slot");
    printf("\n2. list slot");
    printf("\n3. modify slots");
    printf("\n4. delete slots");
    printf("\n5. Profit of Day");
    printf("\n6. Profit of Month");
    printf("\n7. exit menu\n");
    printf("\nEnter Your Choice:");
    scanf("%d", &ch);
    switch (ch) {
    case 1:
      adminwritedata();
      break;
    case 2:
      adminreaddata();
      break;
    case 3:
      adminmodifyslots();
      break;
    case 4:
      admindeleteslots();
      break;
    case 5:
      profitofday();
      break;
    case 6:
      profitofmonth();
      break;
    case 7:
      break;
    default:
      printf("Wrong Choice");
    }
  } while (ch != 7);
}

int passcheck() {
  char pw[20];
  printf("Enter Password :");
  scanf("%s", pw);
  if (strcmp(pw, "admin") == 0) {
    adminmainmenu();
  }
}
void readslots() {
  FILE *f;
  struct turf t;
  f = fopen("turf.dat", "r");
  while (fread(&t, sizeof(struct turf), 1, f)) {
    printf("\nSID : %d\nslot timing : %s  \nfee :%d\n", t.SID, t.slot, t.fee);
  }
  fclose(f);
}

int getbookingid() {
  FILE *f;
  struct Booking b;
  int c = 0;
  f = fopen("booking.dat", "r");
  while (fread(&b, sizeof(struct Booking), 1, f)) {
    c = c + 1;
  }
  fclose(f);
  if (c == 0) {
    return 1000;
  } else {
    return 1000 + c;
  }
}

int slot_display(int d, int m, int y, char slot[15]) {
  FILE *f2;
  struct Booking b;
  int flag = 0;
  f2 = fopen("booking.dat", "r");
  while (fread(&b, sizeof(struct Booking), 1, f2)) {
    if (b.d == d && b.m == m && b.y == y) {

      if (strcmp(b.slot, slot) == 0) {
        flag = 1;
        break;
      }
    }
  }
  fclose(f2);
  if (flag == 0) {
    return 0;
  } else {
    return 1;
  }
}

int cancelbooking() {
  FILE *f;
  struct Booking b;
  int a, flag = 0, pos;
  f = fopen("booking.dat", "r+");
  printf("\nenter booking id :");
  scanf("%d", &a);
  while (fread(&b, sizeof(struct Booking), 1, f)) {
    if (b.bookid == a) {
      printf("\ncustomer name : %s\nphone number : %s\nstatus : "
             "%s\nbooking id : %d\ndate : %d/%d/%d\n",
             b.cname, b.ph, b.stat, b.bookid, b.d, b.m, b.y);
      pos = ftell(f);
      flag = 1;
      break;
    }
  }
  if (flag == 0)
    printf("\nNo such record is found\n");
  else {
    fseek(f, pos - sizeof(b), SEEK_SET);
    strcpy(b.stat, "cancelled");
    fwrite(&b, sizeof(struct Booking), 1, f);
    printf("\nYour booking is cancelled\n");
  }
  fclose(f);
  return 0;
}

void booking() {
  int d, m, y, r, id;
  struct Booking b;
x:
  printf("\nEnter the date for booking (DD/MM/YYYY): ");
  scanf("%d/%d/%d", &d, &m, &y);
  r = checkdate(d, m, y);
  if (r == 0) {
    printf("\nPlease re-enter date\n");
    goto x;
  } else {
    printf("\nwelcome to booking\n");
    readslots();
    printf("\nenter slot : ");
    scanf("%d", &id);
    FILE *f;
    struct turf t;
    int a, flag = 0, pos;
    f = fopen("turf.dat", "r+");
    while (fread(&t, sizeof(struct turf), 1, f)) {
      if (t.SID == id) {
        strcpy(b.slot, t.slot);
        b.fee = t.fee;
        printf("SID : %d\nslot timing : %s fee : %d\n", t.SID, t.slot, t.fee);
      }
    }
    printf("\nenter customer name :");
    scanf("%s", b.cname);
    printf("customer ph no. :");
    scanf("%s", b.ph);
    strcpy(b.stat, "booked");
    b.d = d;
    b.m = m;
    b.y = y;
    b.bookid = getbookingid();
    printf("\ncustomer name : %s\nphone number : %s\nstatus : "
           "%s \nbooking id : "
           "%d\ndate : %d/%d/%d\nslot : %s",
           b.cname, b.ph, b.stat, b.bookid, b.d, b.m, b.y, b.slot);
    f = fopen("booking.dat", "a+");
    fwrite(&b, sizeof(struct Booking), 1, f);
    fclose(f);
  }
}

void searchfile() {
  FILE *f1, *f2;
  struct Booking b;
  struct turf t;
  int d, m, y, flag;
  char ch;
  printf("\nenter date to search (DD/MM/YYYY)");
  scanf("%d/%d/%d", &d, &m, &y);
  f1 = fopen("turf.dat", "r");
  while (fread(&t, sizeof(struct turf), 1, f1)) {
    printf("\n%s", t.slot);
    flag = 0;
    f2 = fopen("booking.dat", "r");
    while (fread(&b, sizeof(struct Booking), 1, f2)) {
      if (b.d == d && b.m == m && b.y == y) {
        if (strcmp(b.slot, t.slot) == 0 && strcmp(b.stat, "booked") == 0) {
          printf(" : booked");
          flag = 1;
        }
      }
    }
    fclose(f2);
    if (flag == 0) {
      printf(" : not booked");
    }
  }
  fclose(f1);
}

int main() {
  int ch;
  do {
    printf("\nMain Menu");
    printf("\n1. Admin");
    printf("\n2. Booking");
    printf("\n3. Search Booking");
    printf("\n4. Cancel Booking");
    printf("\n5. Exit Page");
    printf("\nEnter Your Choice:");
    scanf("%d", &ch);
    switch (ch) {
    case 1:
      passcheck();
      break;
    case 2:
      booking();
      break;
    case 3:
      searchfile();
      break;
    case 4:
      cancelbooking();
      break;
    case 5:
      exit(0);
    default:
      printf("\nWrong Choice\n");
    }
  } while (ch != 5);
}
