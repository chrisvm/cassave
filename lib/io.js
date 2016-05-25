#ifndef node_natives_h
#define node_natives_h
namespace node {

  const unsigned char natives_native[] = {  };

struct _native {
  const char* name;
  const unsigned char* source;
  size_t source_len;
};

static const struct _native natives[] = {   { "natives", natives_native, sizeof(natives_native) },
 };

}
#endif
