#include <wjelement.h>

/*
callback: plop validation errors to stderr
*/
static void schema_error(void *client, const char *format, ...) {
    va_list ap;
    va_start(ap, format);
    vfprintf(stderr, format, ap);
    va_end(ap);
    fprintf(stderr, "\n");
}


int main(int argc, char **argv) {
    FILE *jsonfile;
    FILE *schemafile;
    WJReader readjson;
    WJReader readschema;
    WJElement json;
    WJElement schema;

    if (argc != 3) {
        printf("usage:\n");
        printf("\t%s <json-file> <schema-file>\n", argv[0]);
        return -1;
    }

    jsonfile = fopen(argv[1], "r");
    schemafile = fopen(argv[2], "r");

    readjson = WJROpenFILEDocument(jsonfile, NULL, 0);
    json = WJEOpenDocument(readjson, NULL, NULL, NULL);
    printf("json: %s\n", readjson->depth ? "bad" : "good");

    readschema = WJROpenFILEDocument(schemafile, NULL, 0);
    schema = WJEOpenDocument(readschema, NULL, NULL, NULL);
    printf("schema: %s\n", readschema->depth ? "bad" : "good");

    XplBool valid = WJESchemaValidate(schema, json, schema_error, 0, 0, 0);
    printf("validation: %s\n", valid ? "PASS" : "FAIL");

    WJECloseDocument(json);
    WJECloseDocument(schema);
    WJRCloseDocument(readjson);
    WJRCloseDocument(readschema);

    fclose(jsonfile);
    fclose(schemafile);

    return 0;
}
