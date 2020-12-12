#include <czmq.h>
#include <stdio.h>

int main(int argc, char ** argv) {
  zsock_t *socket = zsock_new_sub("tcp://192.168.0.25:5555", "TOPIC");
  assert(socket);

  char *topic;
  char *frame;
  int state;
  zmsg_t *msg;
  int rc ;
  while(1)
  {
    rc = zsock_recv(socket, "sm", &topic, &msg);
    assert(rc == 0);

    zsys_info("Recv on %s", topic);
    while (frame = zmsg_popstr(msg))
    {
      sscanf(frame, "button state %d", &state);
      if (state)
        printf("LED ON.\n");
      else
        printf("LED OFF.\n");
      free(frame);
    }
    free(topic);
    zmsg_destroy(&msg);
  }

  zsock_destroy(&socket);
  return 0;
}