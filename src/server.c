#include <czmq.h>
#include <button.h>
#include <led.h>
#include <string.h>
#include <unistd.h>

#define _1ms 1000

static Button_t button = {
    .gpio.pin = 7,
    .gpio.eMode = eModeInput,
    .ePullMode = ePullModePullUp,
    .eIntEdge = eIntEdgeFalling,
    .cb = NULL
};

static LED_t led =
    {
        .gpio.pin = 0,
        .gpio.eMode = eModeOutput
    };

static void readButton(void);
static int state = 0;


int main(int argc, char ** argv) {
  char buffer[80];
  zsock_t *socket = zsock_new_pub("tcp://*:5555");
  assert(socket);

  if (Button_init(&button))
    return EXIT_FAILURE;
  
  if (LED_init(&led))
    return EXIT_FAILURE;

  while(!zsys_interrupted) {
    memset(buffer, 0, sizeof(buffer));
    snprintf(buffer, 80, "button state %d", state);
    zsys_info("Publishing");
    zsock_send(socket, "ss", "TOPIC", buffer);
    LED_set(&led, (eState_t)state);
    readButton();
  }

  zsock_destroy(&socket);
  return 0;
}

static void readButton(void)
{
  while (1)
  {
    if (!Button_read(&button))
    {
      usleep(_1ms * 40);
      while (!Button_read(&button))
        ;
      usleep(_1ms * 40);
      state ^= 0x01;
      break;
    }
    else
    {
      usleep(_1ms);
    }
  }
}