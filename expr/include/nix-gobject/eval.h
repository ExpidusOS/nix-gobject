#pragma once

#include <glib.h>

G_BEGIN_DECLS

typedef struct _NixPrimOp {
  NixPrimOpFun fun;
  size_t arity;
  char* name;
  char** args;
  char* doc;
} NixPrimOp;

#ifdef __cplusplus
Nix::PrimOp nix_prim_op_to_native(NixPrimOp* self);
#else
void* nix_prim_op_to_native(NixPrimOp* self);
#endif

G_END_DECLS
