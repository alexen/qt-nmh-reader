set(TARGET_FILE ${CMAKE_BINARY_DIR}/${PROJECT_NAME}.json)

configure_file(
     manifest.json.in
     ${TARGET_FILE}
     @ONLY
)

install(
     FILES ${TARGET_FILE}
     DESTINATION $ENV{HOME}/.config/google-chrome/NativeMessagingHosts/
)
