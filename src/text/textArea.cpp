#include "textArea.h"

textArea::textArea() {
    
}

textArea::textArea(Settings settings) {
    name = settings.name;
    textContent = settings.textContent;
    width = settings.width;
    height = settings.height;
    x = settings.relX;
    y = settings.relY;
    paddingLeft = settings.paddingLeft;
    paddingRight = settings.paddingRight;
    paddingTop = settings.paddingTop;
    paddingBottom = settings.paddingBottom;
    marginLeft = settings.marginLeft;
    marginRight = settings.marginRight;
    marginTop = settings.marginTop;
    marginBottom = settings.marginBottom;
    fontName = settings.fontName;
    fontSize = settings.fontSize;
    textColor = settings.textColor;
    shadowX = settings.shadowX;
    shadowY = settings.shadowY;
    isShadow = settings.isShadow;
    
    build();
}

textArea::~textArea() {
    destroy();
}

void textArea::destroy() {
    //
}

void textArea::build() {
    textBlock.init(fontName, fontSize);
    textBlock.setText(textContent);
    textBlock.wrapTextX(width - paddingLeft - paddingRight);
    textBlock.setColor(textColor);
    
    ofFbo::Settings fboSettings;
    fboSettings.internalformat = GL_RGBA32F_ARB;
    fboSettings.useDepth = true;
    fboSettings.useStencil = true;
    fboSettings.textureTarget = GL_TEXTURE_2D;
    fboSettings.width = width;
    fboSettings.height = height;
    fboSettings.numSamples = 2;
    
    fbo.allocate(fboSettings);
    
    createFBO();
}

void textArea::createFBO() {
    fbo.begin();
    ofClear(0,0,0,255);
    fbo.end();
    
    fbo.begin();
    ofPushStyle();
    ofEnableAlphaBlending();
    ofFill();
    ofSetColor(ofColor(ofRandom(255), ofRandom(255), ofRandom(255)));
    ofRect(0,0,width,height);
    if (isShadow) {
        textBlock.setColor(0, 0, 0, 255);
        textBlock.drawLeft(10 + shadowY, fbo.getHeight() - 10 - textBlock.getHeight() + shadowY);
    }
    textBlock.setColor(textColor);
    textBlock.drawLeft(10, fbo.getHeight() - 10 - textBlock.getHeight());
    ofDisableAlphaBlending();
    ofPopStyle();
    fbo.end();
}

void textArea::draw(ofPoint currentPosition) {
    fbo.getTextureReference().bind();
    glEnable(GL_BLEND);
    glBlendFunc(GL_ONE, GL_ZERO);
    fbo.draw(currentPosition.x, currentPosition.y, width, height);
    glDisable(GL_BLEND);
    fbo.getTextureReference().unbind();
}

ofFbo textArea::getFBO() {
    return fbo;
}

textArea::Settings::Settings() {
    name = "title";
    textContent = "Woot!";
    fontName = "Lato-Bla";
    textColor = ofColor::white;
    shadowColor = ofColor::black;
    backgroundColor = ofColor(ofRandom(255), ofRandom(255), ofRandom(255));
    fontSize = 14;
	width = 0;
	height = 0;
    relX = 0;
    relY = 0;
    paddingLeft = 0;
    paddingRight = 0;
    paddingTop = 0;
    paddingBottom = 0;
    marginLeft = 0;
    marginRight = 0;
    marginTop = 0;
    marginBottom = 0;
    shadowX = 0;
    shadowY = 0;
    isShadow = true;
}