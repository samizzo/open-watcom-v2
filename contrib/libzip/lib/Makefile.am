lib_LTLIBRARIES = libzip.la
noinst_HEADERS = zipint.h
include_HEADERS = zip.h

libzip_la_LDFLAGS=-version-info 0:5

libzip_la_SOURCES=\
	zip_add.c \
	zip_close.c \
	zip_delete.c \
	zip_dirent.c \
	zip_entry_free.c \
	zip_entry_new.c \
	zip_err_str.c \
	zip_error.c \
	zip_error_get.c \
	zip_error_get_sys_type.c \
	zip_error_strerror.c \
	zip_error_to_str.c \
	zip_fclose.c \
	zip_file_error_get.c \
	zip_file_get_offset.c \
	zip_file_strerror.c \
	zip_fopen.c \
	zip_fopen_index.c \
	zip_fread.c \
	zip_free.c \
	zip_get_num_files.c \
	zip_get_name.c \
	zip_name_locate.c \
	zip_new.c \
	zip_open.c \
	zip_rename.c \
	zip_replace.c \
	zip_source_buffer.c \
	zip_source_file.c \
	zip_source_filep.c \
	zip_source_free.c \
	zip_source_function.c \
	zip_source_zip.c \
	zip_set_name.c \
	zip_stat.c \
	zip_stat_index.c \
	zip_strerror.c \
	zip_unchange.c \
	zip_unchange_all.c \
	zip_unchange_data.c

BUILT_SOURCES=zip_err_str.c

EXTRA_DIST=make_zip_err_str.sh

zip_err_str.c: zip.h make_zip_err_str.sh
	sh $(srcdir)/make_zip_err_str.sh $(srcdir)/zip.h zip_err_str.c
