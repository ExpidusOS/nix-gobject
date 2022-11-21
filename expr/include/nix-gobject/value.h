#pragma once

#include <glib.h>

G_BEGIN_DECLS

#define NIX_TYPE_VALUE nix_value_get_type()
G_DECLARE_FINAL_TYPE(NixValue, nix_value, NIX, VALUE, GObject);

struct _NixValue {
  GObject parent_instance;

  /*< private >*/
  struct _NixValuePrivate* priv;
};

#ifdef __cplusplus
NixValue* nix_value_new_from_native(Nix::Value& value);
#endif

GValue* nix_value_to_gvalue(NixValue* value);

G_END_DECLS
