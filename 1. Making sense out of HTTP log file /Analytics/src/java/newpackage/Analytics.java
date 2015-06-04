package newpackage;

import com.mongodb.AggregationOutput;
import com.mongodb.BasicDBObject;
import java.io.IOException;
import java.io.PrintWriter;
import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import com.mongodb.DB;
import com.mongodb.DBCollection;
import com.mongodb.DBCursor;
import com.mongodb.DBObject;
import com.mongodb.MongoClient;
import java.util.ArrayList;
import java.util.List;
import java.util.Random;

/**
 *
 * @author vedangjoshi
 */
public class Analytics extends HttpServlet {

    private String dist;
    int i = 0, j = 0;
  
    protected void processRequest(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        response.setContentType("text/html;charset=UTF-8");

        dist = request.getParameter("Distributions");

        PrintWriter out = response.getWriter();
        try {

            MongoClient client = new MongoClient("localhost", 27017);  //change if port number of MongoDB is not 27017          
            DB myDB = client.getDB("log");            
            DBCollection http = myDB.getCollection("http");
          
            /**
             * MongoClient client = new MongoClient("localhost", Integer.getInteger(getServletConfig().getInitParameter("Port_Number")));
             * DB myDB = client.getDB(getServletConfig().getInitParameter("Database_Name"));
             * DBCollection http = myDB.getCollection(getServletConfig().getInitParameter("Collection_Name")); 
             */
            
            DBCursor cursor = http.find();

            // Request Method
            DBObject group = new BasicDBObject("$group", new BasicDBObject("_id", "$Request_Method").append("total", new BasicDBObject("$sum", 1)));
            AggregationOutput output = http.aggregate(group);
            List<String> method = new ArrayList<String>();
            List<Integer> method_values = new ArrayList<Integer>();
            for (DBObject result : output.results()) {
                method.add((String) result.get("_id"));
                method_values.add((Integer) result.get("total"));
            }

            // Response code
            DBObject group1 = new BasicDBObject("$group", new BasicDBObject("_id", "$Response_Status_code").append("total", new BasicDBObject("$sum", 1)));
            AggregationOutput output1 = http.aggregate(group1);
            List<String> response_code = new ArrayList<String>();
            List<Integer> code_values = new ArrayList<Integer>();
            for (DBObject result : output1.results()) {
                response_code.add((String) result.get("_id"));
                code_values.add((Integer) result.get("total"));
            }

            // Country wise distribution
            DBObject group2 = new BasicDBObject("$group", new BasicDBObject("_id", "$Country").append("total", new BasicDBObject("$sum", 1)));
            DBObject sort2 = new BasicDBObject("$sort", new BasicDBObject("total", -1));
            AggregationOutput output2 = http.aggregate(group2, sort2);
            List<String> country = new ArrayList<String>();
            List<Integer> country_values = new ArrayList<Integer>();
            for (DBObject result : output2.results()) {
                country.add((String) result.get("_id"));
                country_values.add((Integer) result.get("total"));
            }

            out.print("<!DOCTYPE html>");
            out.print("<html>");
            out.print("<head>\n"
                    + "		<meta http-equiv=\"content-type\" content=\"text/html; charset=utf-8\" />\n"
                    + "		\n"
                    + "		<title>DataTables Bootstrap 3 example</title>\n"
                    + "\n"
                    + "		<link rel=\"stylesheet\" \n"
                    + "			  type=\"text/css\"\n"
                    + "			  href=\"bootstrap.min.css\">\n"
                    + "		\n"
                    + "		<link rel=\"stylesheet\" \n"
                    + "			  type=\"text/css\"\n"
                    + "			  href=\"color.js\">\n"
                    + "		\n"
                    + "          <link rel=\"stylesheet\" \n"
                    + "			  type=\"text/css\"\n"
                    + "			  href=\"newcss.css\">\n"
                    + "		\n"
                    + "		<link rel=\"stylesheet\" \n"
                    + "			  type=\"text/css\" \n"
                    + "			  href=\"dataTables.bootstrap.css\">\n"
                    + "\n"
                    + "		<script type=\"text/javascript\"\n"
                    + "			    language=\"javascript\" \n"
                    + "				src=\"jquery-1.11.3.min.js\">\n"
                    + "		</script>\n"
                    + "		\n"
                    + "		<script type=\"text/javascript\" \n"
                    + "		        language=\"javascript\" \n"
                    + "		        src=\"jquery.dataTables.min.js\">\n"
                    + "		</script>\n"
                    + "		\n"
                    + "		<script type=\"text/javascript\" \n"
                    + "	"
                    + "		    language=\"javascript\" \n"
                    + "			    src=\"dataTables.bootstrap.js\">\n"
                    + "		</script>\n"
                    + "		\n"
                    + "		<script type=\"text/javascript\" charset=\"utf-8\">\n"
                    + "			$(document).ready(function() {\n"
                    + "				$('#example').dataTable();\n"
                    + "			} );\n"
                    + "		</script>\n"
                    + "	</head>");
            out.print("<body bgcolor=\"d9edf7\">");
            System.out.println("\n\n\n ***"+ http.getName() +"***\n\n\n");
            out.println();

            if (dist.equals("method")) {
                out.print("<a href=\"index.jsp\"><br>Back</a>"
                        + "<div id=\"pieChart_Method\"></div>"
                        + "</div>");
            } else if (dist.equals("response")) {
                out.print("<a href=\"index.jsp\"><br>Back</a>"
                        + "<div id=\"pieChart_Response\"></div>"
                        + "\t"
                        + "</div>");
            } else if (dist.equals("country")) {
                out.print("<div class=\"container\">");
                out.print("<table id=\"example\" class=\"display\" cellspacing=\"0\" width=\"100%\"> "
                        + "<thead>");
                out.println("<tr>\n"
                        + "<th>" + "Country" + "</th>\n"
                        + "<th>" + "Request Frequency" + "</th>\n"
                        + "</tr>");

                out.println("</thead>");
                out.print("<tbody>\n");
                for (int k = 0; k < country.size(); k++) {
                    out.print("\n\n<tr>");
                    out.println("\n<td>" + country.get(k) + "</td>");
                    out.print("<td>" + country_values.get(k) + "</td>\n");
                    out.print("</tr>");
                }
                out.print("</tbody>");

                out.println("</table>");
                out.print("</div>");

            } else if (dist.equals("packet")) {
                out.print("<div class=\"container\">");
                out.print("<table id=\"example\" class=\"display\" cellspacing=\"0\" width=\"100%\">");
                out.print("<thead>"
                        + "                  <tr>"
                        + "                  <th>Index </th>"
                        + "                  <th>Http-Version</th>"
                        + "                  <th>Request-Method</th>"
                        + "                  <th>Client-Port</th>"
                        + "                  <th>Browser</th>"
                        + "                  <th>IP-address</th>"
                        + "                  <th>Site-name</th>"
                        + "                  <th>Response-Code</th>"
                        + "                  <th>Requested_URI</th>"
                        + "                  </tr>"
                        + "</thead>");

                if (cursor.count() > 0) {
                    int index = 1;
                    out.print("<tbody>");
                    while (cursor.hasNext()) {
                        out.print("<tr>");
                        DBObject obj = cursor.next();
                        out.print("<td>" + index++ + "</td>");
                        out.print("<td>" + obj.get("Http_version") + "</td>");
                        out.print("<td>" + obj.get("Request_Method") + "</td>");
                        out.print("<td>" + obj.get("Port_Number_Client") + "</td>");
                        out.print("<td>" + obj.get("Browser") + "</td>");
                        out.print("<td>" + obj.get("IP_addr_Client") + "</td>");
                        out.print("<td>" + obj.get("Site_name") + "</td>");
                        out.print("<td>" + obj.get("Response_Status_code") + "</td>");
                        out.print("<td>" + obj.get("Request_URI") + "</td>");
                        out.print("</tr>");
                    }
                    out.print("</tbody>");
                    out.println("</table>");
                    out.println("</div>");
                }

                out.print("<script type=\"text/javascript\">\n"
                        + "	// For demo to fit into DataTables site builder...\n"
                        + "	$('#example')\n"
                        + "		.removeClass( 'display' )\n"
                        + "		.addClass('table table-striped table-bordered');\n"
                        + "</script>");

            }

            out.print("<script src=\"./d3.min.js\"></script>\n"
                    + "<script src=\"./d3pie.js\"></script>\n");
           out.print("\n"
                    + "<script>\n"
                    + "var pie = new d3pie(\"pieChart_Method\", {\n"
                    + "	\"header\": {\n"
                    + "		\"title\": {\n"
                    + "			\"text\": \"Response Code\",\n"
                    + "			\"color\": \"#19a48f\",\n"
                    + "			\"fontSize\": 24,\n"
                    + "			\"font\": \"open sans\"\n"
                    + "		},\n"
                    + "		\"subtitle\": {\n"
                    + "			\"text\": \"Distribution of Response Code\","
                    + "			\"color\": \"#774da7\",\n"
                    + "			\"fontSize\": 12,\n"
                    + "			\"font\": \"open sans\"\n"
                    + "		},\n"
                    + "		\"location\": \"top-right\",\n"
                    + "		\"titleSubtitlePadding\": 9\n"
                    + "	},\n"
                    + "	\"footer\": {\n"
                    + "		\"color\": \"#774da7\",\n"
                    + "		\"fontSize\": 12,\n"
                    + "		\"font\": \"open sans\",\n"
                    + "		\"location\": \"bottom-left\"\n"
                    + "	},\n"
                    + "	\"size\": {\n"
                    + "		\"canvasWidth\": 590,\n"
                    + "		\"pieOuterRadius\": \"100%\"\n"
                    + "	},\n"
                    + "	\n"
                    + "	\"data\": {\n"
                    + "		\"sortOrder\": \"value-desc\",\n"
                    + "		\"content\": [\n"
                    + "			{\n"
                    + "				\"label\":\"Response(" + method.get(i) + ")\",\n"
                    + "				\"value\":" + method_values.get(i++) + ",\n"
                    + "				\"color\": \"#ecf0f1\"\n"
                    + "			},\n"
                    + "			{\n"
                    + "				\"label\":\"Response(" + method.get(i) + ")\",\n"
                    + "				\"value\":" + method_values.get(i++) + ",\n"
                    + "				\"color\": \"#774da7\"\n"
                    + "			},\n"
                    + "			{\n"
                    + "				\"label\":\"Response(" + method.get(i) + ")\",\n"
                    + "				\"value\":" + method_values.get(i++) + ",\n"
                    + "				\"color\": \"#e11c16\"\n"
                    + "			},"
                    + "		]\n"
                    + "	},\n"
                    + "\n"
                    + "	\"labels\": {\n"
                    + "		\"outer\": {\n"
                    + "			\"format\": \"label\",\n"
                    + "			\"pieDistance\": 17\n"
                    + "		},\n"
                    + "		\"inner\": {\n"
                    + "			\"hideWhenLessThanPercentage\": 3\n"
                    + "		},\n"
                    + "		\"mainLabel\": {\n"
                    + "			\"fontSize\": 11\n"
                    + "		},\n"
                    + "		\"percentage\": {\n"
                    + "			\"color\": \"#ffffff\",\n"
                    + "			\"decimalPlaces\": 0\n"
                    + "		},\n"
                    + "		\"value\": {\n"
                    + "			\"color\": \"#adadad\",\n"
                    + "			\"fontSize\": 11\n"
                    + "		},\n"
                    + "		\"lines\": {\n"
                    + "			\"enabled\": true,\n"
                    + "			\"color\": \"#871b1b\"\n"
                    + "		},\n"
                    + "		\"truncation\": {\n"
                    + "			\"enabled\": true\n"
                    + "		}\n"
                    + "	},\n"
                    + "	\"tooltips\": {\n"
                    + "		\"enabled\": true,\n"
                    + "		\"type\": \"placeholder\",\n"
                    + "		\"string\": \"{label}: {value}, {percentage}%\",\n"
                    + "		\"styles\": {\n"
                    + "			\"fadeInSpeed\": 369,\n"
                    + "			\"backgroundOpacity\": 0.03\n"
                    + "		}\n"
                    + "	},\n"
                    + "	\"effects\": {\n"
                    + "		\"pullOutSegmentOnClick\": {\n"
                    + "			\"effect\": \"linear\",\n"
                    + "			\"speed\": 400,\n"
                    + "			\"size\": 8\n"
                    + "		}\n"
                    + "	},\n"
                    + "	\"misc\": {\n"
                    + "		\"gradient\": {\n"
                    + "			\"enabled\": true,\n"
                    + "			\"percentage\": 100\n"
                    + "		}\n"
                    + "	}\n"
                    + "});\n"
                    + "</script>");
           
           i=0;
           
            out.print("\n"
                    + "<script>\n"
                    + "var pie = new d3pie(\"pieChart_Response\", {\n"
                    + "	\"header\": {\n"
                    + "		\"title\": {\n"
                    + "			\"text\": \"Response Code\",\n"
                    + "			\"color\": \"#19a48f\",\n"
                    + "			\"fontSize\": 24,\n"
                    + "			\"font\": \"open sans\"\n"
                    + "		},\n"
                    + "		\"subtitle\": {\n"
                    + "			\"text\": \"Distribution of Response Code\","
                    + "			\"color\": \"#774da7\",\n"
                    + "			\"fontSize\": 12,\n"
                    + "			\"font\": \"open sans\"\n"
                    + "		},\n"
                    + "		\"location\": \"top-right\",\n"
                    + "		\"titleSubtitlePadding\": 9\n"
                    + "	},\n"
                    + "	\"footer\": {\n"
                    + "		\"color\": \"#774da7\",\n"
                    + "		\"fontSize\": 12,\n"
                    + "		\"font\": \"open sans\",\n"
                    + "		\"location\": \"bottom-left\"\n"
                    + "	},\n"
                    + "	\"size\": {\n"
                    + "		\"canvasWidth\": 590,\n"
                    + "		\"pieOuterRadius\": \"100%\"\n"
                    + "	},\n"
                    + "	\n"
                    + "	\"data\": {\n"
                    + "		\"sortOrder\": \"value-desc\",\n"
                    + "		\"content\": [\n"
                    + "			{\n"
                    + "				\"label\":\"Response(" + response_code.get(j) + ")\",\n"
                    + "				\"value\":" + code_values.get(j++) + ",\n"
                    + "				\"color\": \"#ecf0f1\"\n"
                    + "			},\n"
                    + "			{\n"
                    + "				\"label\":\"Response(" + response_code.get(j) + ")\",\n"
                    + "				\"value\":" + code_values.get(j++) + ",\n"
                    + "				\"color\": \"#e64d10\"\n"
                    + "			},\n"
                    + "			{\n"
                    + "				\"label\":\"Response(" + response_code.get(j) + ")\",\n"
                    + "				\"value\":" + code_values.get(j++) + ",\n"
                    + "				\"color\": \"#FF99CC\"\n"
                    + "			},\n"
                    + "                 {\n"
                    + "				\"label\":\"Response(" + response_code.get(j) + ")\",\n"
                    + "				\"value\":" + code_values.get(j++) + ",\n"
                    + "				\"color\": \"#99FF66\"\n"
                    + "			},\n"
                    + "                  {\n"
                    + "				\"label\":\"Response(" + response_code.get(j) + ")\",\n"
                    + "				\"value\":" + code_values.get(j++) + ",\n"
                    + "				\"color\": \"#006d91\"\n"
                    + "			},\n"
                    + "                  {\n"
                    + "				\"label\":\"Response(" + response_code.get(j) + ")\",\n"
                    + "				\"value\":" + code_values.get(j++) + ",\n"
                    + "				\"color\": \"#600DC3\"\n"
                    + "			},\n"
                    + "		]\n"
                    + "	},\n"
                    + "\n"
                    + "	\"labels\": {\n"
                    + "		\"outer\": {\n"
                    + "			\"format\": \"label\",\n"
                    + "			\"pieDistance\": 17\n"
                    + "		},\n"
                    + "		\"inner\": {\n"
                    + "			\"hideWhenLessThanPercentage\": 3\n"
                    + "		},\n"
                    + "		\"mainLabel\": {\n"
                    + "			\"fontSize\": 11\n"
                    + "		},\n"
                    + "		\"percentage\": {\n"
                    + "			\"color\": \"#90C29\",\n"
                    + "			\"decimalPlaces\": 0\n"
                    + "		},\n"
                    + "		\"value\": {\n"
                    + "			\"color\": \"#adadad\",\n"
                    + "			\"fontSize\": 11\n"
                    + "		},\n"
                    + "		\"lines\": {\n"
                    + "			\"enabled\": true,\n"
                    + "			\"color\": \"#871b1b\"\n"
                    + "		},\n"
                    + "		\"truncation\": {\n"
                    + "			\"enabled\": true\n"
                    + "		}\n"
                    + "	},\n"
                    + "	\"tooltips\": {\n"
                    + "		\"enabled\": true,\n"
                    + "		\"type\": \"placeholder\",\n"
                    + "		\"string\": \"{label}: {value}, {percentage}%\",\n"
                    + "		\"styles\": {\n"
                    + "			\"fadeInSpeed\": 369,\n"
                    + "			\"backgroundOpacity\": 0.03\n"
                    + "		}\n"
                    + "	},\n"
                    + "	\"effects\": {\n"
                    + "		\"pullOutSegmentOnClick\": {\n"
                    + "			\"effect\": \"linear\",\n"
                    + "			\"speed\": 400,\n"
                    + "			\"size\": 8\n"
                    + "		}\n"
                    + "	},\n"
                    + "	\"misc\": {\n"
                    + "		\"gradient\": {\n"
                    + "			\"enabled\": true,\n"
                    + "			\"percentage\": 100\n"
                    + "		}\n"
                    + "	}\n"
                    + "});\n"
                    + "</script>");

            j = 0;

            out.print("</body>");
            out.print("</html>");
        } finally {
            out.close();
        }
    }

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        processRequest(request, response);
    }

    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        processRequest(request, response);
    }
}
