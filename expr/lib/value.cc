#include <nix-gobject/value.h>

typedef struct _NixValuePrivate {
  Nix::Value& value;
} NixValuePrivate;

G_DEFINE_TYPE_WITH_PRIVATE(NixValue, nix_value, G_TYPE_OBJECT);

enum {
  PROP_0,
  PROP_NATIVE,
  N_PROPERTIES
};

static GParamSpec* obj_props[N_PROPERTIES] = {
  NULL,
};

static void nix_value_finalize(GObject* obj) {
  NixValue* self = NIX_VALUE(obj);

  if (self->priv->native != nullptr) {
    delete self->priv->native;
    self->priv->native = nullptr;
  }

  G_OBJECT_CLASS(nix_value_parent_class)->finalize(obj);
}

static void nix_value_set_property(GObject* obj, guint prop_id, const GValue* value, GParamSpec* pspec) {
  NixValue* self = NIX_VALUE(obj);

  switch (prop_id) {
    case PROP_NATIVE:
      self->priv->native = (Nix::Value&)g_value_get_pointer(obj);
      break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID(obj, prop_id, pspec);
      break;
  }
}

static void nix_value_get_property(GObject* obj, guint prop_id, GValue* value, GParamSpec* pspec) {
  NixValue* self = NIX_VALUE(obj);

  switch (prop_id) {
    case PROP_NATIVE:
      g_value_set_pointer(value, self->priv->native);
      break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID(obj, prop_id, pspec);
      break;
  }
}

static void nix_value_class_init(NixValueClass* klass) {
  GObjectClass* object_class = G_OBJECT_CLASS(klass);

  object_class->finalize = nix_value_finalize;
  object_class->set_property = nix_value_set_property;
  object_class->get_property = nix_value_get_property;

  obj_props[PROP_NATIVE] = g_param_spec_pointer("native", "Nix Native", "Pointer to the native C++ Nix object instance", G_PARAM_FLAGS_PRIVATE | G_PARAM_FLAGS_READWRITE | G_PARAM_FLAGS_CONSTRUCT_ONLY);
  g_object_class_install_properties(object_class, N_PROPERTIES, obj_props);
}

static void nix_value_init(NixValue* self) {
  NixValuePrivate* priv = nix_value_get_instance_private(self);
  self->priv = priv;
}

NixValue* nix_value_new_from_native(Nix::Value& value) {
  return g_object_new(NIX_TYPE_VALUE, "native", value, NULL);
}
