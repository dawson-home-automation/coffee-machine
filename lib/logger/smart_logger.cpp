#include <smart_logger.h>

void info(String action, const char* message) {
  char topic_c[200];
  String topic = "arduino/log/" + action + "/info";
  topic.toCharArray(topic_c, 200);

  publish_message(topic_c, 1, message, false);
}
