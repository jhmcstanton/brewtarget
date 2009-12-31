/*
 * hop.cpp is part of Brewtarget, and is Copyright Philip G. Lee
 * (rocketman768@gmail.com), 2009.
 *
 * Brewtarget is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.

 * Brewtarget is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <iostream>
#include <string>
#include <stdlib.h>
#include "hop.h"
#include "xml.h"
#include "xmlnode.h"
#include "stringparsing.h"
#include "brewtarget.h"
#include <QDomElement>
#include <QDomText>
#include <QObject>

using namespace std;

bool operator<( Hop &h1, Hop &h2 )
{
   return h1.name < h2.name;
}

bool operator==( Hop &h1, Hop &h2 )
{
   return h1.name == h2.name;
}

bool Hop::isValidUse(const string &str)
{
   static const string uses[] = {"Boil", "Dry Hop", "Mash", "First Wort", "Aroma"};
   static const int length = 5;
   
   int i;
   for( i = 0; i < length; ++i )
      if( beginsWith( str, uses[i] ) )
         return true;
         
   return false;
}

bool Hop::isValidType(const string &str)
{
   static const string types[] = {"Bittering", "Aroma", "Both"};
   static const int length = 3;
   
   int i;
   for( i = 0; i < length; ++i )
      if( beginsWith( str, types[i] ) )
         return true;
         
   return false;
}

bool Hop::isValidForm(const string &str)
{
   static const string forms[] = {"Pellet", "Plug", "Leaf", ""};
   static const int length = 4;
   
   int i;
   for( i = 0; i < length; ++i )
      if( beginsWith( str, forms[i] ) )
         return true;
         
   return false;
}

void Hop::toXml(QDomDocument& doc, QDomNode& parent)
{
   QDomElement hopNode;
   QDomElement tmpNode;
   QDomText tmpText;
   
   hopNode = doc.createElement("HOP");
   
   tmpNode = doc.createElement("NAME");
   tmpText = doc.createTextNode(name.c_str());
   tmpNode.appendChild(tmpText);
   hopNode.appendChild(tmpNode);
   
   tmpNode = doc.createElement("VERSION");
   tmpText = doc.createTextNode(text(version));
   tmpNode.appendChild(tmpText);
   hopNode.appendChild(tmpNode);
   
   tmpNode = doc.createElement("ALPHA");
   tmpText = doc.createTextNode(text(alpha_pct));
   tmpNode.appendChild(tmpText);
   hopNode.appendChild(tmpNode);
   
   tmpNode = doc.createElement("AMOUNT");
   tmpText = doc.createTextNode(text(amount_kg));
   tmpNode.appendChild(tmpText);
   hopNode.appendChild(tmpNode);
   
   tmpNode = doc.createElement("USE");
   tmpText = doc.createTextNode(use.c_str());
   tmpNode.appendChild(tmpText);
   hopNode.appendChild(tmpNode);
   
   tmpNode = doc.createElement("TIME");
   tmpText = doc.createTextNode(text(time_min));
   tmpNode.appendChild(tmpText);
   hopNode.appendChild(tmpNode);
   
   tmpNode = doc.createElement("NOTES");
   tmpText = doc.createTextNode(notes.c_str());
   tmpNode.appendChild(tmpText);
   hopNode.appendChild(tmpNode);
   
   tmpNode = doc.createElement("TYPE");
   tmpText = doc.createTextNode(type.c_str());
   tmpNode.appendChild(tmpText);
   hopNode.appendChild(tmpNode);
   
   tmpNode = doc.createElement("FORM");
   tmpText = doc.createTextNode(form.c_str());
   tmpNode.appendChild(tmpText);
   hopNode.appendChild(tmpNode);
   
   tmpNode = doc.createElement("BETA");
   tmpText = doc.createTextNode(text(beta_pct));
   tmpNode.appendChild(tmpText);
   hopNode.appendChild(tmpNode);
   
   tmpNode = doc.createElement("HSI");
   tmpText = doc.createTextNode(text(hsi_pct));
   tmpNode.appendChild(tmpText);
   hopNode.appendChild(tmpNode);
   
   tmpNode = doc.createElement("ORIGIN");
   tmpText = doc.createTextNode(origin.c_str());
   tmpNode.appendChild(tmpText);
   hopNode.appendChild(tmpNode);
   
   tmpNode = doc.createElement("SUBSTITUTES");
   tmpText = doc.createTextNode(substitutes.c_str());
   tmpNode.appendChild(tmpText);
   hopNode.appendChild(tmpNode);
   
   tmpNode = doc.createElement("HUMULENE");
   tmpText = doc.createTextNode(text(humulene_pct));
   tmpNode.appendChild(tmpText);
   hopNode.appendChild(tmpNode);
   
   tmpNode = doc.createElement("CARYOPHYLLENE");
   tmpText = doc.createTextNode(text(caryophyllene_pct));
   tmpNode.appendChild(tmpText);
   hopNode.appendChild(tmpNode);
   
   tmpNode = doc.createElement("COHUMULONE");
   tmpText = doc.createTextNode(text(cohumulone_pct));
   tmpNode.appendChild(tmpText);
   hopNode.appendChild(tmpNode);
   
   tmpNode = doc.createElement("MYRCENE");
   tmpText = doc.createTextNode(text(myrcene_pct));
   tmpNode.appendChild(tmpText);
   hopNode.appendChild(tmpNode);
   
   parent.appendChild(hopNode);
}

void Hop::setDefaults()
{
   name = "";
   use = "Boil";
   notes = "";
   type = "Both";
   form = "Pellet";
   origin = "";
   substitutes = "";
   
   alpha_pct = 0.0;
   amount_kg = 0.0;
   time_min = 0.0;
   beta_pct = 0.0;
   hsi_pct = 0.0;
   humulene_pct = 0.0;
   caryophyllene_pct = 0.0;
   cohumulone_pct = 0.0;
   myrcene_pct = 0.0;
}

Hop::Hop()
{
   setDefaults();
}

Hop::Hop( Hop& other )
        : Observable()
{
   name = other.name;
   alpha_pct = other.alpha_pct;
   amount_kg = other.amount_kg;
   use = other.use;
   time_min = other.time_min;

   notes = other.notes;
   type = other.type;
   form = other.form;
   beta_pct = other.beta_pct;
   hsi_pct = other.hsi_pct;
   origin = other.origin;
   substitutes = other.substitutes;
   humulene_pct = other.humulene_pct;
   caryophyllene_pct = other.caryophyllene_pct;
   cohumulone_pct = other.cohumulone_pct;
   myrcene_pct = other.myrcene_pct;
}

Hop::Hop(const QDomNode& hopNode)
{
   fromNode(hopNode);
}

void Hop::fromNode(const QDomNode& hopNode)
{
   QDomNode node, child;
   QDomText textNode;
   QString property, value;
   
   setDefaults();
   
   for( node = hopNode.firstChild(); ! node.isNull(); node = node.nextSibling() )
   {
      if( ! node.isElement() )
      {
         Brewtarget::log(Brewtarget::WARNING, QObject::tr("Node at line %1 is not an element.").arg(textNode.lineNumber()) );
         continue;
      }
      
      child = node.firstChild();
      if( child.isNull() || ! child.isText() )
         continue;
      
      property = node.nodeName();
      textNode = child.toText();
      value = textNode.nodeValue();
      
      if( property == "NAME" )
      {
         name = value.toStdString();
      }
      else if( property == "VERSION" )
      {
         if( version != getInt(textNode) )
            Brewtarget::log(Brewtarget::ERROR, QObject::tr("HOP says it is not version %1. Line %2").arg(version).arg(textNode.lineNumber()) );
      }
      else if( property == "ALPHA" )
      {
         setAlpha_pct(getDouble(textNode));
      }
      else if( property == "AMOUNT" )
      {
         setAmount_kg(getDouble(textNode));
      }
      else if( property == "USE" )
      {
         if( isValidUse(value.toStdString()) )
            setUse(value.toStdString());
         else
            Brewtarget::log(Brewtarget::ERROR, QObject::tr("%1 is not a valid use for HOP. Line %2").arg(value).arg(textNode.lineNumber()) );
      }
      else if( property == "TIME" )
      {
         setTime_min(getDouble(textNode));
      }
      else if( property == "NOTES" )
      {
         setNotes(value.toStdString());
      }
      else if( property == "TYPE" )
      {
         if( isValidType(value.toStdString()) )
            setType(value.toStdString());
         else
            Brewtarget::log(Brewtarget::ERROR, QObject::tr("%1 is not a valid type for HOP. Line %2").arg(value).arg(textNode.lineNumber()) );
      }
      else if( property == "FORM" )
      {
         if( isValidForm(value.toStdString()) )
            setForm(value.toStdString());
         else
            Brewtarget::log(Brewtarget::ERROR, QObject::tr("%1 is not a valid form for HOP. Line %2").arg(value).arg(textNode.lineNumber()) );
      }
      else if( property == "BETA" )
      {
         setBeta_pct(getDouble(textNode));
      }
      else if( property == "HSI" )
      {
         setHsi_pct(getDouble(textNode));
      }
      else if( property == "ORIGIN" )
      {
         setOrigin(value.toStdString());
      }
      else if( property == "SUBSTITUTES" )
      {
         setSubstitutes(value.toStdString());
      }
      else if( property == "HUMULENE" )
      {
         setHumulene_pct(getDouble(textNode));
      }
      else if( property == "CARYOPHYLLENE" )
      {
         setCaryophyllene_pct(getDouble(textNode));
      }
      else if( property == "COHUMULONE" )
      {
         setCohumulone_pct(getDouble(textNode));
      }
      else if( property == "MYRCENE" )
      {
         setMyrcene_pct(getDouble(textNode));
      }
      else
         Brewtarget::log(Brewtarget::WARNING, QObject::tr("Unsupported HOP property: %1. Line %2").arg(property).arg(node.lineNumber()) );
   }
}

//============================="SET" METHODS====================================
void Hop::setName( const string &str )
{
   name = string(str);
   hasChanged();
}

void Hop::setAlpha_pct( double num )
{
   if( num < 0.0 || num > 100.0 )
      throw HopException("Bad percentage: " + doubleToString(num));
   else
   {
      alpha_pct = num;
      hasChanged();
   }
}

void Hop::setAmount_kg( double num )
{
   if( num < 0.0 )
      throw HopException("Bad amount: " + doubleToString(num));
   else
   {
      amount_kg = num;
      hasChanged();
   }
}

// Returns true on success, false on failure.
bool Hop::setUse( const string &str )
{
   if( isValidUse(str) )
   {
      use = string(str);
      hasChanged();
      return true;
   }
   else
      return false;
}

void Hop::setTime_min( double num )
{
   if( num < 0.0 )
      throw HopException("Bad time: " + doubleToString(num));
   else
   {
      time_min = num;
      hasChanged();
   }
}
      
void Hop::setNotes( const string &str )
{
   notes = string(str);
   hasChanged();
}

bool Hop::setType( const string &str )
{
   if( isValidType(str) )
   {
      type = string(str);
      hasChanged();
      return true;
   }
   else
      return false;
}

bool Hop::setForm( const string &str )
{
   if( isValidForm(str) )
   {
      form = string(str);
      hasChanged();
      return true;
   }
   else
      return false;
}

void Hop::setBeta_pct( double num )
{
   if( num < 0.0 || num > 100.0 )
      throw HopException("Bad percentage: " + doubleToString(num));
   else
   {
      beta_pct = num;
      hasChanged();
   }
}

void Hop::setHsi_pct( double num )
{
   if( num < 0.0 || num > 100.0 )
      throw HopException("Bad percentage: " + doubleToString(num));
   else
   {
      hsi_pct = num;
      hasChanged();
   }
}

void Hop::setOrigin( const string &str )
{
   origin = string(str);
   hasChanged();
}

void Hop::setSubstitutes( const string &str )
{
   substitutes = string(str);
   hasChanged();
}

void Hop::setHumulene_pct( double num )
{
   if( num < 0.0 || num > 100.0 )
      throw HopException("Bad percentage: " + doubleToString(num));
   else
   {
      humulene_pct = num;
      hasChanged();
   }
}

void Hop::setCaryophyllene_pct( double num )
{
   if( num < 0.0 || num > 100.0 )
      throw HopException("Bad percentage: " + doubleToString(num));
   else
   {
      caryophyllene_pct = num;
      hasChanged();
   }
}

void Hop::setCohumulone_pct( double num )
{
   if( num < 0.0 || num > 100.0 )
      throw HopException("Bad percentage: " + doubleToString(num));
   else
   {
      cohumulone_pct = num;
      hasChanged();
   }
}

void Hop::setMyrcene_pct( double num )
{
   if( num < 0.0 || num > 100.0 )
      throw HopException("Bad percentage: " + doubleToString(num));
   else
   {
      myrcene_pct = num;
      hasChanged();
   }
}

//============================="GET" METHODS====================================

const string& Hop::getName() const
{
   return name;
}

int Hop::getVersion() const
{
   return version;
}

double Hop::getAlpha_pct() const
{
   return alpha_pct;
}

double Hop::getAmount_kg() const
{
   return amount_kg;
}

const string& Hop::getUse() const
{
   return use;
}

double Hop::getTime_min() const
{
   return time_min;
}

const string& Hop::getNotes() const
{
   return notes;
}

const string& Hop::getType() const
{
   return type;
}

const string& Hop::getForm() const
{
   return form;
}

double Hop::getBeta_pct() const
{
   return beta_pct;
}

double Hop::getHsi_pct() const
{
   return hsi_pct;
}

const string& Hop::getOrigin() const
{
   return origin;
}

const string& Hop::getSubstitutes() const
{
   return substitutes;
}

double Hop::getHumulene_pct() const
{
   return humulene_pct;
}

double Hop::getCaryophyllene_pct() const
{
   return caryophyllene_pct;
}

double Hop::getCohumulone_pct() const
{
   return cohumulone_pct;
}

double Hop::getMyrcene_pct() const
{
   return myrcene_pct;
}
