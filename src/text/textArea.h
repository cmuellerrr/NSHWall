#include "ofMain.h"
#include "ofxTextSuite.h"

// 1. Collect resources

class textArea {
    
public:
    
    struct Settings;
    
    textArea();
    textArea(Settings settings);
    ~textArea();
    
    vector<textArea> children;
    
    ofFbo getFBO();
    
    void destroy();
    void drawChildren();
    void build();
    void createFBO();
    void update();
    void draw(ofPoint currentPosition);
    void addChild(Settings settings);
    void getChild(string name);
    
    struct Settings {
        string name;
        string textContent;
        string fontName;
        ofColor textColor;
        ofColor backgroundColor;
        ofColor shadowColor;
        int fontSize;
        int width;
        int height;
        int relX;
        int relY;
        int paddingLeft;
        int paddingRight;
        int paddingTop;
        int paddingBottom;
        int marginLeft;
        int marginRight;
        int marginTop;
        int marginBottom;
        int shadowX;
        int shadowY;
        float shadowBlur;
        bool isShadow;
        
		Settings();
	};
    
protected:
    string name;
    string textContent;
    string fontName;
    ofFbo textAreaFBO;
    ofColor backgroundColor;
    ofColor textColor;
    ofxTextBlock textBlock;
    
    int x;
    int y;
    
    int width;
    int height;
    
    int paddingLeft;
    int paddingRight;
    int paddingTop;
    int paddingBottom;
    int marginLeft;
    int marginRight;
    int marginTop;
    int marginBottom;
    int shadowX;
    int shadowY;
    bool isShadow;
    
    int fontSize;
    
    ofFbo fbo;
    
private:
    int id;
    
};