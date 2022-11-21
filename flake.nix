{
  description = "Nix package manager and language for GObject";

  inputs.expidus-sdk = {
    url = github:ExpidusOS/sdk;
  };

  outputs = { self, expidus-sdk }:
    expidus-sdk.lib.expidus.flake.make {
      inherit self;
      name = "nix-gobject";
      packagesFor = { final, prev, old }: {
        overlay = {
          nix-gobject = final.stdenv.mkDerivation {
            pname = "nix-gobject";
            version = self.shortRev or "dirty";

            outputs = [ "out" "dev" ];
            src = self;

            nativeBuildInputs = with final; [ meson ninja pkg-config vala final.expidus-sdk ];
            buildInputs = with final; [ nix glib ];

            meta = with final.lib; {
              description = "Nix package manager and language for GObject";
              homepage = "https://github.com/ExpidusOS/nix-gobject";
              license = licenses.gpl3Only;
              maintainers = with expidus.maintainers; [ TheComputerGuy ];
            };
          };
        };
      };
    };
}
