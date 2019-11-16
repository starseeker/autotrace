add_test(NAME github-000008-run-1
	COMMAND autotrace -output-file "${CMAKE_CURRENT_BINARY_DIR}/trace01.svg" -output-format svg "${CMAKE_CURRENT_SOURCE_DIR}/trace01.bmp"
	)

add_test(NAME github-000008-run-2
	COMMAND autotrace -output-file "${CMAKE_CURRENT_BINARY_DIR}/trace02.svg" -output-format svg "${CMAKE_CURRENT_SOURCE_DIR}/trace02.bmp"
	)

add_test(NAME github-000008-run-3
	COMMAND autotrace -centerline -output-file "${CMAKE_CURRENT_BINARY_DIR}/trace01_c.svg" -output-format svg -report-progress "${CMAKE_CURRENT_SOURCE_DIR}/trace01.bmp"
	)

add_test(NAME github-000008-run-4
	COMMAND autotrace -centerline -output-file "${CMAKE_CURRENT_BINARY_DIR}/trace02_c.svg" -output-format svg -report-progress "${CMAKE_CURRENT_SOURCE_DIR}/trace02.bmp"
	)

