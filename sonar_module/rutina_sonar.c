#include <stdio.h>        
#include <string.h>       
#include <unistd.h>       
#include <fcntl.h>        
#include <errno.h>        
#include <termios.h>       
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/ioctl.h>

#define BUFLEN 30
struct termios old_cfg;  
int ser_dev;            // identificator dispozitiv serial   

/*
 * Functie responsabila cu deschiderea portului serial pentru comunicatia RS232.
 * Returneaza file descriptorul asociat dispozitivului tty sau -1 in cazul unei erori.
 */

int open_serial_port(char *port)
{
  int fd;            // file descriptor pentru port
  // se deschide portul ttyS0 cu urmatoarele moduri de acces
  // O_RDWR - deschidere pentru citire si scriere
  // O_NOCTTY  - dispozitivul terminal nu va controla procesul curent
  // O_NDELAY - parametru intarziere
  fd = open(port, O_RDWR | O_NOCTTY); // | O_NONBLOCK overrides VTIME and VMIN
  if (fd == -1) {

    printf("open_serial_port : Nu se poate deschide %s !\n", port);
  } else
    // functie file control
    // seteaza flagurile de stare ale fisierului dat de un file descriptor     
    fcntl(fd, F_SETFL);

  return (fd);
}

/*
 * Functie care implementeaza comportamentul la finalizarea comunicatiei.
 * - se elibereaza buferele de TX si RX si se elibereaza conexiunea seriala.
 */
void close_serial_port(int s)
{
  // elibereaza datele scrise in bufferul de TX dar care nu au fost transmise
  // si datele care au fost receptionate in bufferul de RX dar nu au fost citite
  // pentru conexiunea 0
  tcsetattr(ser_dev,TCSANOW,&old_cfg);
  tcflush(s, TCIOFLUSH);
  // se inchide conexiunea seriala
  close(s);
}


/*
Functie care este responsabila cu setarea parametrilor de comunicatie pe linia seriala RS232

- seteaza viteza de comunicatie la transmisie si receptie
- seteaza reprezentarea caracterelor in informatia transmisa (5/6/7/8 biti / caracter)
- seteaza paritatea (N - none, E - even, O - odd) utila in detectia erorilor de transmisie
- seteaza numarul de biti de stop

Informatia privind parametrii de transmisie se seteaza intr-o instanta a structurii struct termios
unde se incapsuleaza informatie privind parametrii pentru intrare, iesire, moduri de control,
moduri locale si caractere de control.
*/

int setup_serial_port(int s, struct termios *cfg, int speed, int data,
         unsigned char parity, int stopb)
{
  // se initializeaza instanta de configurare la valorile specifice OS
  tcgetattr(s, cfg);
  // seteaza instanta de configurare a portului serial la valori default ale atributelor
  cfmakeraw(cfg);
  // retine baudrate-ul
  speed_t baudrate;
  switch (speed) {        // preia viteza
  case 9600:
    baudrate = B9600;
    break;
  case 19200:
    baudrate = B19200;
    break;
  case 38400:
    baudrate = B38400;
    break;
  case 57600:
    baudrate = B57600;
    break;
  case 115200:
    baudrate = B115200;
    break;
  default:
          baudrate=B9600;
    break;
  }

  // scrie in instanta structurii termios cfg valoarea de configurare
  // pentru viteza pe RX din variabila baudrate                   
  cfsetispeed(cfg, baudrate);
  // scrie in instanta structurii termios cfg valoarea de configurare
  // pentru viteza pe TX din variabila baudrate
  cfsetospeed(cfg, baudrate);

  // preia paritatea si seteaza campul corespunzator din structura de configurare

  switch (parity | 32) {
  case 'n':{            //  fara valoare de paritate
      // dezactiveaza generarea valorii de paritatae la TX
      // si verificarea paritarii la RX 
      cfg->c_cflag &= ~PARENB;
      break;
    }
  case 'e':            // valoare de paritate para
    {
      // activeaza generarea valorii de paritate la TX si verificare la RX
      cfg->c_cflag |= PARENB;
      // activeaza verificarea paritatii la TX si RX pt valoare para
      cfg->c_cflag &= ~PARODD;
      break;
    }
  case 'o':            // valoare de paritate impara
    {
      // activeaza generarea valorii de paritate la TX si verificare la RX
      cfg->c_cflag |= PARENB;
      // activeaza verificarea paritatii la TX si RX pt valoare impara
      cfg->c_cflag |= PARODD;
      break;
    }
  }
  // masca pentru setarea dimensiunii unui caracter in informatia transmisa
  cfg->c_cflag &= ~CSIZE;
  // se extrage capacitatea de reprezentare a unui caracter
  switch (data) {
    // seteaza campul corespunzator reprezentarii
    // unui caracter cu macroul corespunzator
  case 5:
    {
      cfg->c_cflag |= CS5;    // 5 biti / char
      break;
    }
  case 6:
    {
      cfg->c_cflag |= CS6;    // 6 biti / char
      break;
    }
  case 7:
    {
      cfg->c_cflag |= CS7;    // 7 biti / char
      break;
    }
  case 8:
    {
      cfg->c_cflag |= CS8;    // 8 biti / char
      break;
    }
  }
  // se extrage numerul de biti de stop si ajusteaza valoare de configurare
  if (stopb == 1) {
    cfg->c_cflag &= ~CSTOPB;    // seteaza un bit de STOP
  } else {
    cfg->c_cflag |= CSTOPB;    // seteaza 2 biti de STOP

  }
  /* enable canonical input */
  cfg->c_iflag &= ~ICRNL;
  cfg->c_oflag &= ~OCRNL;
  cfg->c_cflag |= (CLOCAL | CREAD);
  //cfg->c_lflag |= ICANON;
  cfg->c_cc[VMIN] = BUFLEN;
  cfg->c_cc[VTIME] = 0;
  // seteaza valorile de configurare primite la intrare si setate in structura termios
  // pentru portul serial considerat in s
  // setarea are loc imediat si apoi se revine cu un cod de return intreg
  return tcsetattr(s, TCSANOW, cfg);
}

int main(int argc, char **argv)
{
  char buf[BUFLEN];        // buffer date RX/TX
  struct termios cfg;        // structura cu date de configurare a portului serial
  int nbytes;            // numarul de octeti cititi
  int ret;            // cod de return
  char *intro;		//antet pachet
  /* delimitator pentru datele din pachetele seriale */
  const char delimiters[] = ",";
  /* valori string ale citirilor de la sonar */
  char *sonar1_rd, *sonar2_rd, *sonar3_rd, *sonar4_rd, *sonar5_rd;
  long val_s1, val_s2, val_s3, val_s4, val_s5;
  char *cp;
  int mcr = 0; // modem control

  printf("Connecting to the serial port ....\n");
  if ((ser_dev = open_serial_port("/dev/ttyS1")) == -1){
    printf("Cannot open serial port %d!\n",
          ser_dev);
    exit(1);
  }
  printf("Serial port opened !\n");
  tcgetattr(ser_dev,&old_cfg); 
  printf("Configuring serial port ...\n");
  if ((ret = setup_serial_port(ser_dev, &cfg, 9600, 8, 'n', 1))< 0) {
    printf("Serial port %d cannot be configured !\n",
          ser_dev);
    exit(1);
  }
  printf("Serial port is configured !\n");

  signal(SIGTERM, close_serial_port);
  printf("Start reading on the serial port ....\n");

  /* reinitialize the modem */
  ioctl(ser_dev, TIOCMGET, &mcr);
  mcr &= ~TIOCM_DTR;
  ioctl(ser_dev, TIOCMSET, &mcr);
  sleep(1);
  ioctl(ser_dev, TIOCMGET, &mcr);
  mcr |= TIOCM_DTR;
  ioctl(ser_dev, TIOCMSET, &mcr);
  printf("modem was reset ! \n");

 while (1) {
	while((nbytes = read(ser_dev, buf, BUFLEN)==BUFLEN)){
	buf[BUFLEN]='\0';
        cp = strdup(buf);
	printf("%s\n", cp);
	if(!cp) continue ;
	intro = strtok(buf, delimiters);
	if(!intro)continue;
        if(strcmp(intro,">")!=0) continue;
        val_s1 = strtol(strtok(NULL, delimiters), NULL, 16);
        val_s2 = strtol(strtok(NULL, delimiters), NULL, 16);
        val_s3 = strtol(strtok(NULL, delimiters), NULL, 16);
        val_s4 = strtol(strtok(NULL, delimiters), NULL, 16);
        val_s5 = strtol(strtok(NULL, delimiters), NULL, 16);
	if((val_s1==0) || (val_s2==0) || (val_s3==0) || (val_s4==0) || (val_s5==0)) continue;
        printf("%ld | %ld | %ld | %ld | %ld \n", 
		val_s1, 
		val_s2, 
		val_s3, 
		val_s4, 
		val_s5);
   }
 }
  return 0;
}
