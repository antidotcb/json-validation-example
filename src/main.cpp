#include <wjelement.h>
#include <iostream>

using std::cout;
using std::endl;

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
        cout << "usage:" << endl;
        cout << "\t" << argv[0] << "<json-file> <schema-file>" << endl;
        return -1;
    }

    jsonfile = fopen(argv[1], "r");
    schemafile = fopen(argv[2], "r");

    readjson = WJROpenFILEDocument(jsonfile, NULL, 0);
    json = WJEOpenDocument(readjson, NULL, NULL, NULL);
    cout << "JSON:\t\t" << (!readjson->depth ? "PASS" : "FAIL") << endl;

    readschema = WJROpenFILEDocument(schemafile, NULL, 0);
    schema = WJEOpenDocument(readschema, NULL, NULL, NULL);
    cout << "JSON SCHEMA:\t" << (!readschema->depth ? "PASS" : "FAIL") << endl;

    XplBool valid = WJESchemaValidate(schema, json, schema_error, 0, 0, 0);
    cout << "JSON VALID:\t" << (valid ? "PASS" : "FAIL") << endl;

    WJECloseDocument(json);
    WJECloseDocument(schema);
    WJRCloseDocument(readjson);
    WJRCloseDocument(readschema);

    fclose(jsonfile);
    fclose(schemafile);

    return 0;
}
