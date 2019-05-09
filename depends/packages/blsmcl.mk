#Boneh–Lynn–Shacham (BLS) signature scheme
#Origin from https://github.com/herumi/bls
#This package is configured only for Ubuntu building. 
#For other OS (Windows, MacOSX, Linux-ARM) you must to build on native environment as static library.
package=blsmcl
$(package)_version=1.0
$(package)_download_path=https://github.com/tzcytpm/blsmcl/releases/download/1.0
$(package)_file_name=blsmcl.tar.gz
$(package)_sha256_hash=AB1502D6539E0C7E84A3B1C4841C10120A5E27CB66C9858A569EEA6DA8848511

define $(package)_set_vars
$(package)_build_opts=CC="$($(package)_cc)"
endef

define $(package)_build_cmds
  $(MAKE)
endef

define $(package)_stage_cmds
  mkdir -p $($(package)_staging_prefix_dir)/include/bls $($(package)_staging_prefix_dir)/lib &&\
	install include/bls/* $($(package)_staging_prefix_dir)/include/bls &&\
  install lib/*.a $($(package)_staging_prefix_dir)/lib &&\
  mkdir -p $($(package)_staging_prefix_dir)/include/mcl $($(package)_staging_prefix_dir)/lib &&\
  install mcl/include/mcl/*.* $($(package)_staging_prefix_dir)/include/mcl &&\
  install mcl/lib/*.a $($(package)_staging_prefix_dir)/lib &&\
  mkdir -p $($(package)_staging_prefix_dir)/include/mcl/impl &&\
  install mcl/include/mcl/impl/* $($(package)_staging_prefix_dir)/include/mcl/impl
endef
