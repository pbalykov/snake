{ pkgs ? import<nixpkgs>{} }:

with pkgs;

stdenv.mkDerivation {
  name = "snake";
  src = ./.;
  buildInputs = [ pkgs.ncurses ];
  nativeBuildInputs = [ pkgs.pkg-config ];
  enableParallelBuilding = true;

  installPhase = ''
    mkdir -p $out/bin
    cp Snake $out/bin/
  '';
}
