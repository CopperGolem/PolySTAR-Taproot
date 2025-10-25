{
  description = "PolyStar's Nix Shell";

  inputs = {
    nixpkgs.url = "github:nixos/nixpkgs/nixpkgs-unstable";
    nixpkgsOld.url = "github:nixos/nixpkgs/nixos-23.05";
    flake-utils.url = "github:numtide/flake-utils";
  };

  outputs = { self, nixpkgs, nixpkgsOld, flake-utils }:
  flake-utils.lib.eachDefaultSystem (system:
    let
      pkgs = import nixpkgs {
        inherit system;
      };

      pkgsOld = import nixpkgsOld {
        inherit system;
      };

      gcc10 = pkgsOld.gcc10;
      gcc-arm-embedded10 = pkgsOld.gcc-arm-embedded-10;

      python = pkgs.python3;
      pythonPackages = python.pkgs;

    in {
      devShell = pkgs.mkShell {
        nativeBuildInputs = with pkgs; [
          pkg-config
          gcc-arm-embedded10
          gcc10
          binutils
          scons
          gnumake
          automake
          clang-tools
          git
          doxygen
          gtest
          pkgsOld.bear
          pkgsOld.glibc
        ];

        buildInputs = with pkgs; [
          python
          pythonPackages.pip
          pythonPackages.setuptools
          pythonPackages.virtualenv
          pythonPackages.pyelftools
          pythonPackages.standard-telnetlib
          pythonPackages.jinja2
          pipenv
          stlink
          openocd
          boost
          libusb1
        ];

      shellHook = ''
        python --version
        g++ --version
      '';
    };
  });
}