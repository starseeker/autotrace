add_test(NAME github-000004-run
	COMMAND autotrace -report-progress -filter-iterations 0 -error-threshold 1 -centerline "${CMAKE_CURRENT_SOURCE_DIR}/testrect.pbm" -output-format svg -output-file "${CMAKE_CURRENT_BINARY_DIR}/testrect.svg"
	)

add_test(NAME github-000004-cmp
	COMMAND ${CMAKE_COMMAND} -E compare_files ${CMAKE_CURRENT_SOURCE_DIR}/testrect.output.svg ${CMAKE_CURRENT_BINARY_DIR}/testrect.svg
	)
set_property(TEST github-000004-cmp APPEND PROPERTY DEPENDS github-000004-run)
