compile: extract
	lv_i18n compile -t 'translations/*.yml' -o 'src/lv_i18n'

extract:
	lv_i18n extract -s 'src/**/*.+(c|cpp|h|hpp)' -t 'translations/*.yml'
