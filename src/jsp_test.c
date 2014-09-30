#include <pebble.h>

#include "jsonparser.h"

#define TEST(f, str, exp_len, exp_res) { \
  uint16_t length= 0; \
  JSP_ErrorType result = f(str, &length); \
  if (result == exp_res && length == exp_len) APP_LOG(APP_LOG_LEVEL_INFO, "OK    %s", str); \
  else if (exp_res != JSP_OK && result == exp_res) APP_LOG(APP_LOG_LEVEL_INFO, "OK    %s", str); \
  else APP_LOG(APP_LOG_LEVEL_ERROR, "ERROR %s (length is %d should be %d | result is %d should be %d )", str, length, exp_len, result, exp_res); \
}

char* json_ok = "{\"cod\":\"200\",\"message\":0.0044,\"city\":{\"id\":3080165,\"name\":\"Zielona Gora\",\"coord\":{\"lon\":15.50643,\"lat\":51.935478},\"country\":\"PL\",\"population\":0},\"cnt\":5,\"list\":[{\"dt\":1411898400,\"temp\":{\"day\":10.49,\"min\":7.42,\"max\":10.49,\"night\":7.42,\"eve\":10.49,\"morn\":10.49},\"pressure\":1030.82,\"humidity\":81,\"weather\":[{\"id\":801,\"main\":\"Clouds\",\"description\":\"few clouds\",\"icon\":\"02n\"}],\"speed\":2.51,\"deg\":212,\"clouds\":20},{\"dt\":1411984800,\"temp\":{\"day\":14.88,\"min\":7.39,\"max\":19.32,\"night\":12.81,\"eve\":19.32,\"morn\":7.39},\"pressure\":1029.75,\"humidity\":76,\"weather\":[{\"id\":802,\"main\":\"Clouds\",\"description\":\"scattered clouds\",\"icon\":\"03d\"}],\"speed\":3.41,\"deg\":228,\"clouds\":44},{\"dt\":1412071200,\"temp\":{\"day\":17.7,\"min\":11.54,\"max\":20.24,\"night\":15.11,\"eve\":19.35,\"morn\":11.54},\"pressure\":1029.36,\"humidity\":79,\"weather\":[{\"id\":501,\"main\":\"Rain\",\"description\":\"moderate rain\",\"icon\":\"10d\"}],\"speed\":2.67,\"deg\":268,\"clouds\":68,\"rain\":10},{\"dt\":1412157600,\"temp\":{\"day\":17.88,\"min\":12.99,\"max\":17.88,\"night\":12.99,\"eve\":15.64,\"morn\":15.43},\"pressure\":1025.38,\"humidity\":0,\"weather\":[{\"id\":500,\"main\":\"Rain\",\"description\":\"light rain\",\"icon\":\"10d\"}],\"speed\":4.22,\"deg\":259,\"clouds\":86,\"rain\":2.13},{\"dt\":1412244000,\"temp\":{\"day\":16.06,\"min\":9.24,\"max\":16.06,\"night\":9.24,\"eve\":13.36,\"morn\":13.71},\"pressure\":1028.64,\"humidity\":0,\"weather\":[{\"id\":500,\"main\":\"Rain\",\"description\":\"light rain\",\"icon\":\"10d\"}],\"speed\":5.11,\"deg\":310,\"clouds\":35,\"rain\":0.97}]}";
char* example = "{\"name\":\"test\", \"num\":5, \"array\":[1, 2 ], \"object\":{\"type\":\"some type\", \"value\":\"some value\"}, \"array_of_object\":[{\"name\":\"john\", \"age\":20 }, {\"name\":\"anna\", \"age\":21 } ], \"object_with_array\":{\"team\":[\"adam\", \"tom\", \"moni\"], \"strangers\":[\"kathy\", \"rolf\"]}}";
char* string_ok = "\"string\"";

char* type_labels[] = {"JSP_VALUE_UNKNOWN", "JSP_VALUE_STRING", "JSP_VALUE_OBJECT", "JSP_VALUE_ARRAY", "JSP_VALUE_PRIMITIVE"};

void object_callback(JSP_ValueType type, char* label, uint16_t label_length, char* value, uint16_t value_length) {
  char* l = calloc(label_length + 1, sizeof(char)); 
  char* v = calloc(value_length + 1, sizeof(char)); 

  snprintf(l, label_length + 1, "%s", label); 
  snprintf(v, value_length + 1, "%s", value); 

  APP_LOG(APP_LOG_LEVEL_INFO, "object_callback for type %19s -> %s : %s)", type_labels[type], l, v);

  free(v); 
  free(l); 
}

void array_callback(JSP_ValueType type, char* value, uint16_t value_length) {
  char* v = calloc(value_length + 1, sizeof(char)); 

  snprintf(v, value_length + 1, "%s", value); 

  APP_LOG(APP_LOG_LEVEL_INFO, " array_callback for type %19s -> %s)", type_labels[type], v);

  free(v); 
}

void json_parser_test(void) {
/*
  TEST(string_length, "", 0, JSP_EMPTY);
  TEST(string_length, " ", 0, JSP_ERROR_NOT_STRING);
  TEST(string_length, "\"\"", 2, JSP_OK);
  TEST(string_length, "\"string\"", 8, JSP_OK);
  TEST(string_length, "\"string", 0, JSP_ERROR_UNEXPECTED_END);


  TEST(primitive_length, "", 3, JSP_EMPTY);
  TEST(primitive_length, ",", 0, JSP_ERROR_UNEXPECTED_END);
  TEST(primitive_length, "123,rest", 3, JSP_OK);
  TEST(primitive_length, "123}rest", 3, JSP_OK);
  TEST(primitive_length, "123]rest", 3, JSP_OK);
  TEST(primitive_length, "123 rest", 3, JSP_OK);
  TEST(primitive_length, "123\nrest", 3, JSP_OK);
  TEST(primitive_length, "123\rrest", 3, JSP_OK);
  TEST(primitive_length, "1.23, rest", 4, JSP_OK);
  TEST(primitive_length, "1234", 4, JSP_ERROR_UNEXPECTED_END);
  TEST(primitive_length, "1.234", 5, JSP_ERROR_UNEXPECTED_END);
  TEST(primitive_length, "1", 1, JSP_ERROR_UNEXPECTED_END);  
  TEST(primitive_length, "123\"", 4, JSP_ERROR_UNEXPECTED_QUOTE);
  TEST(primitive_length, "text", 4, JSP_ERROR_UNEXPECTED_CHAR_IN_PRIMITIVE);
  TEST(primitive_length, "123text", 4, JSP_ERROR_UNEXPECTED_CHAR_IN_PRIMITIVE);
  TEST(primitive_length, "1.23text", 4, JSP_ERROR_UNEXPECTED_CHAR_IN_PRIMITIVE);
*/
/*
  TEST(spaces_length, "    a", 4, JSP_OK);
  TEST(spaces_length, "    {", 4, JSP_OK);
  TEST(spaces_length, "    }", 4, JSP_OK);
  TEST(spaces_length, "    ,", 4, JSP_OK);
  TEST(spaces_length, "    \n", 4, JSP_OK);
  TEST(spaces_length, "    \"", 4, JSP_OK);
  TEST(spaces_length, "", 0, JSP_EMPTY);
  TEST(spaces_length, "    ", 0, JSP_ERROR_UNEXPECTED_END);
*/
/*
  TEST(object_length, "{}", 2, JSP_OK);
  TEST(object_length, "{2}", 3, JSP_OK);
  TEST(object_length, "123}", 0, JSP_ERROR_NOT_OBJECT);
  TEST(object_length, "{123", 0, JSP_ERROR_UNEXPECTED_END);

  TEST(object_length, "{123{456}678}", 13, JSP_OK);
  TEST(object_length, "{{456}678}", 10, JSP_OK);
  TEST(object_length, "{123{456}}", 10, JSP_OK);
  TEST(object_length, "{123{}678}", 10, JSP_OK);
  TEST(object_length, "{123{456678}", 0, JSP_ERROR_UNEXPECTED_END);

  TEST(array_length, "[]", 2, JSP_OK);
  TEST(array_length, "[2]", 3, JSP_OK);
  TEST(array_length, "123]", 0, JSP_ERROR_NOT_ARRAY);
  TEST(array_length, "[123", 0, JSP_ERROR_UNEXPECTED_END);

  TEST(array_length, "[123[456]678]", 13, JSP_OK);
  TEST(array_length, "[[456]678]", 10, JSP_OK);
  TEST(array_length, "[123[456]]", 10, JSP_OK);
  TEST(array_length, "[123[]678]", 10, JSP_OK);
  TEST(array_length, "[123[456678]", 0, JSP_ERROR_UNEXPECTED_END);
*/
  JSP_ErrorType error;

  json_register_callbacks(object_callback, array_callback);
  error = json_parser(json_ok);
  APP_LOG(APP_LOG_LEVEL_DEBUG, "Result 0x%x\n", error);

}

int main(void) {

  json_parser_test();

}
