#include "ofMain.h"
#include "ofxTextSuite.h"

// 1. Collect resources

class textArea {
    
public:
    
    struct Settings;
    
    enum textHorizontalAlignment {
        LEFT,
        RIGHT,
        CENTER,
        JUSTIFY
    };
    
    enum textVerticalAlignment {
        TOP,
        MIDDLE,
        BOTTOM
    };
    
    enum boxHeight {
        AUTO_HEIGHT,
        FIXED_HEIGHT
    };
    
    enum boxWidth {
        AUTO_WIDTH,
        FIXED_WIDTH
    };
    
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
        textHorizontalAlignment horizontalAlignment;
        textVerticalAlignment verticalAlignment;
        boxHeight boxHeight;
        boxWidth boxWidth;
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
    textHorizontalAlignment horizontalAlignment;
    textVerticalAlignment verticalAlignment;
    boxHeight boxHeight;
    boxWidth boxWidth;
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